library(readr)
library(tidyverse)

# load fragstats results for patch level
fragstats_patch <- read_csv("data-raw/fragstats_results_patch.txt")

# filter for augusta_nlcd raster
fragstats_patch_augusta_nlcd <- fragstats_patch %>%
    filter(str_detect(LID, 'augusta_nlcd'))

# filter for landscape raster
fragstats_patch_landscape <- fragstats_patch %>%
         filter(str_detect(LID, 'landscape.tif'))

# filter for landscape raster stack
fragstats_patch_landscapestack <- fragstats_patch %>%
    filter(str_detect(LID, 'landscape_stack'))

# filter for podlasie raster
fragstats_patch_podlasie <- fragstats_patch %>%
    filter(str_detect(LID, 'podlasie'))

# save --------------------------------------------------------------------
devtools::use_data(fragstats_patch_augusta_nlcd, overwrite = TRUE)
devtools::use_data(fragstats_patch_landscape, overwrite = TRUE)
devtools::use_data(fragstats_patch_landscapestack, overwrite = TRUE)
devtools::use_data(fragstats_patch_podlasie, overwrite = TRUE)