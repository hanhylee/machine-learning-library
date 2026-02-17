# linear regression

an estimator that fits a linear model with coefficients w = (w_1, w_2, ..., w_p) to minimize the residual sum of squares between observed and predicted targets. we do this by estimating the predictions then improving the coefficients using gradient descent.

## initial estimation

we multiply the feature matrix with an Xavier initialized matrix to get the first set of predictions. then we calculate the error vector by subtracting each prediction with the actual result.

## gradient descent loop

at the start of each loop, we multiply the transposed feature matrix by the error vector.

each value in the gradient vector tells us how to adjust each coefficient:
- if a gradient value is large and positive, the corresponding feature coefficient has an error that grows rapidly as its value increases, thus suggesting that we should decrease the coefficient
- if a gradient value is negative, it means that increasing the corresponding feature coefficient reduces the error, thus suggesting that we should increase the coefficient

we nudge each coefficient by the learning rate (alpha).

B_j = B_j +/- alpha (i.e. 0.01) * gradient value;

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
