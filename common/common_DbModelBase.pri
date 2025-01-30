
COMMON_PATH = $$PWD

INCLUDEPATH *= $$COMMON_PATH
INCLUDEPATH *= $$COMMON_PATH/..

###### НЕ РАЗКОМЕНТИРОВЫВАТЬ!!! 'CONFIG *=' в текущем проекте #####
###### добавлять во внутрь своего .pro файла! #####
#CONFIG *= common_DbModelBase
##########################################DbModelBase########################################
common_DbModelBase  {
    SOURCES *= \
        $$COMMON_PATH/DbModelBase/dbmodelbase.cpp \

    HEADERS *= \
        $$COMMON_PATH/DbModelBase/dbmodelbase.h
}
