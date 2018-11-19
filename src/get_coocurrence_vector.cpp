#define DARMA_64BIT_WORD 1
#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

#include "get_adjacency.h"

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
IntegerMatrix rcpp_get_coocurrence_matrix(arma::imat x, arma::imat directions) {

    // get unique values
    arma::ivec u = arma::conv_to<arma::ivec>::from(arma::unique(x.elem(find(x != INT_MIN))));

    // create a matrix of zeros of unique values size
    arma::imat cooc_mat(u.n_elem, u.n_elem, arma::fill::zeros);

    // extract adjency pairs
    List pairs = rcpp_get_pairs(x, directions);

    IntegerVector center_cells = pairs[0];
    IntegerVector neigh_cells = pairs[1];

    // number of pairs
    int num_pairs = center_cells.length();

    // for each row and col
    for (int i = 0; i < num_pairs; i++) {

        // extract value of central cell and its neighbot
        int center = center_cells(i);
        int neigh = neigh_cells(i);

        // find their location in the output matrix
        arma::uvec loc_c = find(u == center);
        arma::uvec loc_n = find(u == neigh);

        // add its count
        cooc_mat(loc_c, loc_n) += 1;

    }

    // return a coocurence matrix
    IntegerMatrix cooc_mat_result = as<IntegerMatrix>(wrap(cooc_mat));

    // add names
    List u_names = List::create(u, u);
    cooc_mat_result.attr("dimnames") = u_names;
    return cooc_mat_result;
}

// [[Rcpp::export]]
int triangular_index(int r, int c) {
    r++;
    c++;
    if (c <= r){
        return (r - 1) * r / 2 + c - 1;
    } else {
        return (c - 1) * c / 2 + r - 1;
    }
}

// [[Rcpp::export]]
NumericVector rcpp_get_coocurrence_vector(arma::imat x, arma::imat directions, bool ordered = true) {
    NumericVector result;
    // calculate a coocurrence matrix
    x = as<arma::imat>(rcpp_get_coocurrence_matrix(x, directions));
    if (ordered){
        result = as<NumericVector>(wrap(x));
    } else {
        // get a coocurence matrix dimension (it is equal to nrow and ncol)
        int num_e = x.n_cols - 1;
        // Unique combinations number
        int uc = triangular_index(num_e, num_e) + 1;
        // create an empty vector of the unique combinations size
        NumericVector hist(uc);
        // populate a histogram
        for (int i = 0; i <= num_e; i++) {
            for (int j = 0; j <= num_e; j++) {
                hist(triangular_index(i, j)) += x(i, j);
            }
        }
        // every value of neighborhood was calculated twice, therefore divide by 2
        // return a coocurrence vector
        result = as<NumericVector>(wrap(hist / 2));
    }
    // remove a dim attribute
    result.attr("dim") = R_NilValue;
    return result;
}

// [[Rcpp::export]]
NumericVector rcpp_get_offdiagonal_vector(arma::imat x, arma::imat directions) {
    // calculate a coocurrence matrix
    x = as<arma::imat>(rcpp_get_coocurrence_matrix(x, directions));
    // extract off-diagonal
    arma::ivec offdiag = arma::conv_to<arma::ivec>::from(x.elem(find(trimatl(x, -1) != 0)));
    // return a vector
    NumericVector result = as<NumericVector>(wrap(offdiag));
    // remove a dim attribute
    result.attr("dim") = R_NilValue;
    return result;
}

// [[Rcpp::export]]
NumericVector moving_filter(arma::imat x, arma::imat directions) {

    // get unique values
    arma::ivec u = arma::conv_to<arma::ivec>::from(arma::unique(x.elem(find(x != INT_MIN))));

    int nrows = x.n_rows();
    int ncols = x.n_cols();

    // create neighbors coordinates
    IntegerMatrix neigh_coords = rcpp_create_neighborhood(directions);
    int neigh_len = neigh_coords.nrow();

    // loop through x
    for (int i = 0; i < ncols; i++) {
        // loop through y
        for (int j = 0; j < nrows; j++) {
            // loop through neighbors of focal cell
            IntegerVector neighs(neigh_len);
            for (int h = 0; h < neigh_len; h++) {

                // grab coordinates of neighbor
                unsigned neigh_x = i + neigh_coords(h,1);
                unsigned neigh_y = j + neigh_coords(h,0);

                // save value of this neighbor
                neighs[h] = x(neigh_y,neigh_x);
            }

            // store and update values of neighs

            // ????; table from neighs and put that somehow in a matrix
            IntegerVector table(na_omit(neighs));
        }
    }
}

/*** R

*/
