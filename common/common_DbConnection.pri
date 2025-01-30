
COMMON_PATH = $$PWD

INCLUDEPATH *= $$COMMON_PATH
INCLUDEPATH *= $$COMMON_PATH/..

###### НЕ РАЗКОМЕНТИРОВЫВАТЬ!!! 'CONFIG *=' в текущем проекте #####
###### добавлять во внутрь своего .pro файла! #####
#CONFIG *= common_DbConnection

##########################################DbConnection########################################
common_DbConnection  {
    QT += sql
    SOURCES *= \
        $$COMMON_PATH/DbConnection/dbconnection.cpp \

    HEADERS *= \
        $$COMMON_PATH/DbConnection/dbconnection.h
}
