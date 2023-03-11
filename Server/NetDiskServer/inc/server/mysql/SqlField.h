#pragma once
//
// Created by li on 2020/3/24.
//

#define SQL_TYPE(TYPE) SQL_TYPE_##TYPE
#define SQL_TYPE_STRING std::string
#define SQL_TYPE_INT int32_t
#define SQL_TYPE_DOUBLE double
#define SQL_TYPE_DATE std::string
#define SQL_TYPE_BOOL bool

#define FIELD_STRING(NAME) SQL_TYPE(STRING) NAME

#define STRINGNIFY(N) #N
