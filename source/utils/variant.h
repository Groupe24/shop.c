#pragma once

#define VARIANT_STRING_SIZE 128
#define VARIANT_SERIALIZED_SIZE 256

typedef enum
{
    VARIANT_INT,
    VARIANT_FLOAT,
    VARIANT_STRING,
} VarianType;

typedef struct
{
    VarianType type;

    union {
        int as_int;
        float as_float;
    };

    char as_string[VARIANT_STRING_SIZE];
} Variant;

Variant vint(int value);

Variant vfloat(float value);

Variant vstring(const char *value);

Variant vstringf(const char *fmt, ...);

int variant_cmp(Variant left, Variant right);

Variant variant_deserialize(const char *source);

void variant_serialize(Variant value, char *destination);
