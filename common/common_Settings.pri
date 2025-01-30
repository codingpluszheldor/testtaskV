
COMMON_PATH = $$PWD

INCLUDEPATH *= $$COMMON_PATH
INCLUDEPATH *= $$COMMON_PATH/..

###### НЕ РАЗКОМЕНТИРОВЫВАТЬ!!! 'CONFIG *=' в текущем проекте #####
###### добавлять во внутрь своего .pro файла! #####
#CONFIG *= common_Settings

##########################################Settings########################################
common_Settings  {
    SOURCES *= \
        $$COMMON_PATH/Settings/settings.cpp

    HEADERS *= \
        $$COMMON_PATH/Settings/settings.h
}
