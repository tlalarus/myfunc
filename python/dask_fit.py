from glob import glob
import joblib

import dask.dataframe as dd
import dask.array as da
import dask.bag as db
import pyarrow.parquet as pq

import yaml
if __name__ == "__main__":

    with open('/home/minkyung/source/myfunc/python/dask_fit.yaml') as f:
        var_yaml = yaml.load(f, Loader=yaml.FullLoader)
    src_path = var_yaml['src_path']

    for path in src_path:
        print('read', path)
        df = dd.read_parquet(path)
        print(df.head())

    print(df.count().compute())

    cols_ft = ['LDO', 'THETACORR', 'THETASTDEV', 'LENGTHCORR', 'LENGTHSTDEV', 'ROTATE',
       'ROTATEAVG', 'ROTATEMED', 'MVDIST', 'PLENDIFF', 'PLENDIFFMED',
       'PLENDIFFAVG', 'PLENDIFFCORR', 'NMARK', 'LENGTHSCORE']

    dask_X = df[cols_ft].to_dask_array(lengths=True)
    dask_y = df['GT'].to_dask_array(lengths=True)
    print('dask array shape', dask_X.shape, dask_y.shape)

    X = dask_X.compute()
    y = dask_y.compute()
    print('numpy array shape:', X.shape, y.shape)

    # test, validation, train data split
    from sklearn.model_selection import train_test_split

    train_size = 0.8
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size)

    print('x_train shape:', X_train.shape)
    print('y_train shape:', y_train.shape)

    print('y_test shape:', X_test.shape)
    # 
    from sklearn.tree import DecisionTreeClassifier
    from sklearn.metrics import classification_report
    from sklearn.model_selection import GridSearchCV

    from sklearn.ensemble import AdaBoostClassifier
    from sklearn.feature_selection import SelectKBest, mutual_info_classif
    from sklearn.pipeline import Pipeline
    from sklearn.utils import class_weight

    pipe_ = Pipeline([
        ('selector', SelectKBest(mutual_info_classif, k=5)),
        ('classifier', AdaBoostClassifier())
    ])
    params_ = {
        'selector__k': [10, 13, 14],
        'classifier__base_estimator' : [DecisionTreeClassifier(max_depth=10)],
        'classifier__n_estimators': [170],
        'classifier__learning_rate': [0.01, 0.05, 0.1]
    }

    classes_weights = class_weight.compute_sample_weight(class_weight='balanced', y=y_train)

    print('class weight:', len(classes_weights))

    # fit params
    fit_params_ = {
        'classifier__sample_weight' : classes_weights
    }

    grid = GridSearchCV(pipe_, param_grid=params_, scoring='f1', cv=10, verbose=3, n_jobs=-1)
    grid.fit(X_train, y_train, **fit_params_)

    print('Best param', grid.best_params_)
    print('Best estimator', grid.best_estimator_)

    best_sel = grid.best_estimator_.named_steps['selector']
    best_est = grid.best_estimator_.named_steps['classifier']

    # evaluation
    X_sel = best_sel.fit_transform(X_test, y_test)
    pred = best_est.predict(X_sel)

    print('adaboost report')
    print(classification_report(y_test, pred))

    joblib.dump(best_sel, './best_sel.pkl')
    joblib.dump(best_est, './best_est.pkl')
