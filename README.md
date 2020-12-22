
<!-- README.md is generated from README.Rmd. Please edit that file -->

| Continuous Integration                                                                                                                                                          | Development                                                                                                                | CRAN                                                                                                                                                 | License                                                                                                         |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| ![R-CMD-check](https://github.com/r-spatialecology/landscapemetrics/workflows/R-CMD-check/badge.svg)                                                                            | [![lifecycle](https://img.shields.io/badge/lifecycle-stable-brightgreen.svg)](https://www.tidyverse.org/lifecycle/#stable) | [![CRAN status](https://www.r-pkg.org/badges/version/landscapemetrics)](https://cran.r-project.org/package=landscapemetrics)                         | [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) |
| [![Coverage](https://codecov.io/gh/r-spatialecology/landscapemetrics/branch/master/graph/badge.svg)](https://codecov.io/github/r-spatialecology/landscapemetrics?branch=master) | [![Project Status](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)                 | [![CRAN downloads](http://cranlogs.r-pkg.org/badges/grand-total/landscapemetrics)](http://cran.rstudio.com/web/packages/landscapemetrics/index.html) | [![DOI](https://img.shields.io/badge/DOI-10.1111/ecog.04617-blue.svg)](https://doi.org/10.1111/ecog.04617)      |

# landscapemetrics <img src="man/figures/logo.png" align="right" width="150" />

## Overview

**landscapemetrics** is an R package for calculating landscape metrics
for categorical landscape patterns in a tidy workflow. The package can
be used as a drop-in replacement for FRAGSTATS (McGarigal *et al.*
2012), as it offers a reproducible workflow for landscape analysis in a
single environment. It also allows for calculations of four theoretical
metrics of landscape complexity: a marginal entropy, a conditional
entropy, a joint entropy, and a mutual information (Nowosad and
Stepinski 2019).

**landscapemetrics** supports `raster` spatial objects and takes
`RasterLayer`, `RasterStacks`, `RasterBricks` or lists of `RasterLayer`
as input arguments. Every function can be used in a piped workflow, as
it always takes the data as the first argument and returns a tibble.

### Citation

To cite **landscapemetrics** or acknowledge its use, please cite the
following Software note, substituting the version of the application
that you used for ‘ver. 0’:

<p>

<i> Hesselbarth, M.H.K., Sciaini, M., With, K.A., Wiegand, K., Nowosad,
J. 2019. landscapemetrics: an open‐source R tool to calculate landscape
metrics. Ecography, 42: 1648-1657 (ver. 0). </i>

</p>

For more information see [Publication
record](https://r-spatialecology.github.io/landscapemetrics/articles/articles/publication_record.html)
vignette. The get a BibTex entry, please use
`citation("landscapemetrics")`.

## Installation

There are several ways to install **landscapemetrics**:

``` r
# Get the stable version from CRAN
install.packages("landscapemetrics")

# Alternatively, you can install the development version from Github
# install.packages("devtools")
devtools::install_github("r-spatialecology/landscapemetrics")
```

#### Announcement

Due to an improved connected-component labelling algorithm
(**landscapemetrics** v1.4 and higher), patches are labeled in a
different order than before and therefore different patch IDs might be
used compared to previous versions. However, results for all metrics are
identical.

## Using landscapemetrics

The resolution of a raster cell has to be in **meters**, as the package
converts units internally and returns results in either meters, square
meters or hectares. Before using **landscapemetrics**, be sure to check
your raster (see `check_raster()`).

All functions in **landscapemetrics** start with `lsm_` (for
landscapemetrics). The second part of the name specifies the level
(patch - `p`, class - `c` or landscape - `l`). The last part of the
function name is the abbreviation of the corresponding metric
(e.g. `enn` for the euclidean nearest-neighbor distance):

    # general structure
    lsm_"level"_"metric"
    
    # Patch level
    ## lsm_p_"metric"
    lsm_p_enn()
    
    # Class level
    ## lsm_c_"metric"
    lsm_c_enn()
    
    # Landscape level
    ## lsm_p_"metric"
    lsm_l_enn()

All functions return an identical structured tibble:

| layer | level     | class | id | metric           | value |
| ----- | --------- | ----- | -- | ---------------- | ----- |
| 1     | patch     | 1     | 1  | landscape metric | x     |
| 1     | class     | 1     | NA | landscape metric | x     |
| 1     | landscape | NA    | NA | landscape metric | x     |

### Using metric functions

Every function follows the same implementation design, so the usage is
quite straightforward:

``` r
library(landscapemetrics)
library(landscapetools)

# landscape raster
show_landscape(landscape)
```

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" />

``` r

# calculate for example the Euclidean nearest-neighbor distance on patch level
lsm_p_enn(landscape)
#> [90m# A tibble: 27 x 6[39m
#>    layer level class    id metric value
#>    [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m [3m[90m<int>[39m[23m [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m  [3m[90m<dbl>[39m[23m
#> [90m 1[39m     1 patch     1     1 enn     7   
#> [90m 2[39m     1 patch     1     2 enn     4   
#> [90m 3[39m     1 patch     1     3 enn     2.83
#> [90m 4[39m     1 patch     1     4 enn     2   
#> [90m 5[39m     1 patch     1     5 enn     2   
#> [90m 6[39m     1 patch     1     6 enn     2.83
#> [90m 7[39m     1 patch     1     7 enn     4.12
#> [90m 8[39m     1 patch     1     8 enn     4.12
#> [90m 9[39m     1 patch     1     9 enn     4.24
#> [90m10[39m     1 patch     2    10 enn     4.47
#> [90m# … with 17 more rows[39m

# calculate the total area and total class edge length
lsm_l_ta(landscape)
#> [90m# A tibble: 1 x 6[39m
#>   layer level     class    id metric value
#>   [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m     [3m[90m<int>[39m[23m [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m  [3m[90m<dbl>[39m[23m
#> [90m1[39m     1 landscape    [31mNA[39m    [31mNA[39m ta      0.09
lsm_c_te(landscape)
#> [90m# A tibble: 3 x 6[39m
#>   layer level class    id metric value
#>   [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m [3m[90m<int>[39m[23m [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m  [3m[90m<dbl>[39m[23m
#> [90m1[39m     1 class     1    [31mNA[39m te       180
#> [90m2[39m     1 class     2    [31mNA[39m te       227
#> [90m3[39m     1 class     3    [31mNA[39m te       321
```

There is also a wrapper around every metric in the package to quickly
calculate a bunch of metrics:

``` r
# calculate all metrics on patch level
calculate_lsm(landscape, level = "patch")
#> Warning: Please use 'check_landscape()' to ensure the input data is valid.
#> [90m# A tibble: 324 x 6[39m
#>    layer level class    id metric  value
#>    [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m [3m[90m<int>[39m[23m [3m[90m<int>[39m[23m [3m[90m<chr>[39m[23m   [3m[90m<dbl>[39m[23m
#> [90m 1[39m     1 patch     1     1 area   0.000[4m1[24m
#> [90m 2[39m     1 patch     1     2 area   0.000[4m5[24m
#> [90m 3[39m     1 patch     1     3 area   0.014[4m8[24m
#> [90m 4[39m     1 patch     1     4 area   0.000[4m1[24m
#> [90m 5[39m     1 patch     1     5 area   0.000[4m1[24m
#> [90m 6[39m     1 patch     1     6 area   0.001[4m4[24m
#> [90m 7[39m     1 patch     1     7 area   0.000[4m3[24m
#> [90m 8[39m     1 patch     1     8 area   0.000[4m5[24m
#> [90m 9[39m     1 patch     1     9 area   0.000[4m1[24m
#> [90m10[39m     1 patch     2    10 area   0.003[4m5[24m
#> [90m# … with 314 more rows[39m
```

### Utility functions

**landscapemetrics** further provides several visualization functions,
e.g. show all labeled patches or the core area of all patches. All
visualization functions start with the prefix `show_`
(e.g. `show_cores()`).

Important building blocks of the package are exported to help facilitate
analysis or the development of new metrics. They all start with the
prefix `get_`. All of them are implemented with Rcpp and have either
memory or performance advantages compared to raster functions.

For more details, see the [utility
function](https://r-spatialecology.github.io/landscapemetrics/articles/articles/utility.html)
vignette.

### Contributing

One of the major motivations behind **landscapemetrics** is the idea to
provide an open-source code collection of landscape metrics. This
includes, besides bug reports, especially the idea to include new
metrics and functions. Therefore, in case you want to suggest new
metrics or functions and in the best case even contribute code, we
warmly welcome to do so\! For more information see
[CONTRIBUTING](CONTRIBUTING.md).

Maintainers and contributors must follow this repository’s [CODE OF
CONDUCT](CODE_OF_CONDUCT.md).

### References

  - McGarigal, K., Cushman, S.A., and Ene E. 2012. FRAGSTATS v4: Spatial
    Pattern Analysis Program for Categorical and Continuous Maps.
    Computer software program produced by the authors at the University
    of Massachusetts, Amherst. Available at the following website:
    <http://www.umass.edu/landeco/research/fragstats/fragstats.html>
  - Nowosad J., TF Stepinski. 2019. Information theory as a consistent
    framework for quantification and classification of landscape
    patterns. <https://doi.org/10.1007/s10980-019-00830-x>
