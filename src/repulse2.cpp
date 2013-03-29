Rcpp::NumericMatrix nodes(nodesS);
double charge = as<double>(chargeS);
Rcpp::NumericMatrix weight(weightS);
double alpha = as<double>(alphaS);

double currw, thresh;
int n = nodes.nrow();

Rcpp::NumericMatrix disp(nodes.nrow(), nodes.ncol());
disp.fill(0.0);

for (int i = 0; i < n; i++) {
  currw = weight[i];
  for (int j = i+1; j < n; j++) {
        
    double dx = nodes(i, 0) - nodes(j, 0);
    double dy = nodes(i, 1) - nodes(j, 1);
    double l = sqrt(pow(dx, 2) + pow(dy, 2));
    
    thresh = currw + weight[j];
    
    if (l < thresh){
      double k = alpha * charge / pow(l, 2);
  
      disp(i, 0) -= dx * k;
      disp(i, 1) -= dy * k;
      disp(j, 0) += dx * k;
      disp(j, 1) += dy * k;
    }    
  }
}

return disp;
