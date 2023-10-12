#ifndef __AGGREGATORS__
#define __AGGREGATORS__

#include "Dtype.h"
#include "MExprcppEnums.h"

/* =========== Top LEVEL ===================*/


class Aggregator {

    private:

    protected:
        mexprcpp_agg_t agg_id;
        Dtype *aggregator;
        Aggregator();

    public:
        virtual ~Aggregator();
        virtual void aggregate (Dtype *new_data) = 0;\
        static Aggregator *factory (mexprcpp_agg_t agg_type, mexprcpp_dtypes_t dtype);
        Dtype *getAggregatedValue ();
}; 


/* =========== Mid LEVEL ===================*/


class AggMax : public Aggregator {

    private:

    protected:
         AggMax();

    public:
        ~AggMax();
        virtual void aggregate  (Dtype *new_data) = 0;
} ;

class AggMin : public Aggregator {

    private:

    protected:
        AggMin();

    public:
        ~AggMin();
        virtual void aggregate  (Dtype *new_data) = 0;
} ;



/* =========== Bottom LEVEL ===================*/

class AggMaxInt : public AggMax {

    private:

    protected:

    public:
        
        AggMaxInt(Dtype_INT  *agg);
        ~AggMaxInt();
        virtual void aggregate  (Dtype *new_data) override;
};

class AggMaxDouble : public AggMax {

    private:

    protected:

    public:
        AggMaxDouble();
        ~AggMaxDouble();
        virtual void aggregate  (Dtype *new_data) override;
};


class AggMinInt : public AggMin {

    private:

    protected:

    public:
        AggMinInt(Dtype_INT  *agg);
        ~AggMinInt();
        virtual void aggregate  (Dtype *new_data) override;
};

class AggMinDouble : public AggMin{

    private:

    protected:

    public:
        AggMinDouble();
        ~AggMinDouble();
        virtual void aggregate  (Dtype *new_data) override;
};


#endif 
