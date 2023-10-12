#include "Aggregators.h"


/* =========== Top LEVEL ===================*/

Aggregator::Aggregator() {

    this->agg_id = MATH_CPP_AGG_MAXX;
    this->aggregator = NULL;
}

Aggregator::~Aggregator() {

    if (this->aggregator->del_after_use)
        delete this->aggregator;

    this->aggregator = NULL;
    this->agg_id = MATH_CPP_AGG_MAXX;
}

Dtype *
Aggregator::getAggregatedValue () {

    return this->aggregator;
}



/* =========== Mid LEVEL ===================*/

AggMax::AggMax() {

    this->agg_id = MATH_CPP_AGG_MAX;
}

AggMax::~AggMax() {

}


AggMin::AggMin() {

    this->agg_id = MATH_CPP_AGG_MIN;
}

AggMin::~AggMin() {

}




/* =========== Bottom LEVEL ===================*/


AggMaxInt::AggMaxInt (Dtype_INT  *agg) {

    this->aggregator = agg;
    agg->dtype.int_val = INT32_MIN;
}

AggMaxInt::~AggMaxInt() {}

void 
AggMaxInt::aggregate (Dtype *new_dtype) {

    Dtype_INT *new_dtype_int = dynamic_cast <Dtype_INT *> (new_dtype);
    Dtype_INT *this_dtype_int = dynamic_cast <Dtype_INT *> (this->aggregator);
    
    if (this_dtype_int->dtype.int_val < new_dtype_int->dtype.int_val )
        this_dtype_int->dtype.int_val = new_dtype_int->dtype.int_val;

}


AggMinInt::AggMinInt (Dtype_INT  *agg) {

    this->aggregator = agg;
    agg->dtype.int_val = INT32_MAX;
}

AggMinInt::~AggMinInt() {}

void 
AggMinInt::aggregate (Dtype *new_dtype) {

    Dtype_INT *new_dtype_int = dynamic_cast <Dtype_INT *> (new_dtype);
    Dtype_INT *this_dtype_int = dynamic_cast <Dtype_INT *> (this->aggregator);
    
    if (this_dtype_int->dtype.int_val > new_dtype_int->dtype.int_val )
        this_dtype_int->dtype.int_val = new_dtype_int->dtype.int_val;

}



/* ========================== factory Method =====================*/

Aggregator *
Aggregator::factory (mexprcpp_agg_t agg_type, mexprcpp_dtypes_t dtype) {

    switch (agg_type) {

        case MATH_CPP_AGG_COUNT:
            break;



        case MATH_CPP_AGG_MAX:
            
            switch (dtype) {

                case MATH_CPP_INT:
                    return new AggMaxInt (new Dtype_INT());
            }
            break;



        case MATH_CPP_AGG_MIN:

            switch (dtype) {

                case MATH_CPP_INT:
                    return new AggMinInt (new Dtype_INT());
            }
            break;



        case MATH_CPP_AGG_AVG:
            break;
        case MATH_CPP_AGG_SUM:
            break;
        case MATH_CPP_AGG_MUL:
            break;
        default:   
            return NULL;
    }
    return NULL;
}