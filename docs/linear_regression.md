# linear regression

an estimator that fits a linear model with coefficients w = (w_1, w_2, ..., w_p) to minimize the residual sum of squares between observed and predicted targets.

## attributes

**coefficients: *map***
  coefficients estimated during linear regression. if *fit* was only called on a single target, returns a map with feature names as keys and their corresponding coefficients as values. if *fit* was called on multiple targets, returns a map of features names with values corresponding to an their coefficients per target (i.e. an array where index *i* corresponds to target *i*).

## methods

**fit(X, y)**
  fits a linear model to the given features and targets.

  @param
  - X: *array-like of shape (n_samples, n_features)*
    training data.
  - y: *array-like of shape (n_samples,) or (n_samples, n_targets)*
    target value(s).
  
  @return
  - self: *object*
    fitted estimator.

**get_params()**
  get parameters for this estimator.

  @return
  - params: *map*
    parameter names mapped to their values.

**predict(X)**
  predict targets using the linear model

  @param
  - X: *array-like of shape (n_samples, n_features)*
    samples.
  
  @return
  - C: *array, shape (n_samples,)*
    predicted targets.

**score(X, y)**
  calculates the coefficient of determination on test data.
  
  the coefficient of determination, *R^2*, is defined as (1 - *u*/*v*) where *u* is the residual sum of squares (y_true - y_pred)^2.sum() and *v* is the total sum of squares (y_true - y_true.mean())^2.sum().

  @param
  - X: *array-like of shape (n_samples, n_features)*
    training data.
  - y: *array-like of shape (n_samples,) or (n_samples, n_targets)*
    target value(s).

  @return
  - score: *float*
    R^2 of self.predict(X) with respect to y.
