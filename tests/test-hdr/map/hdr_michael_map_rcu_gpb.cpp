//$$CDS-header$$

#include "map/hdr_map.h"
#include <cds/urcu/general_buffered.h>
#include <cds/container/michael_kvlist_rcu.h>
#include <cds/container/michael_map_rcu.h>

namespace map {
    namespace {
        struct map_traits: public cc::michael_map::traits
        {
            typedef HashMapHdrTest::hash_int            hash;
            typedef HashMapHdrTest::simple_item_counter item_counter;
        };
        typedef cds::urcu::gc< cds::urcu::general_buffered<> > rcu_type;

        struct RCU_GPB_cmp_traits: public cc::michael_list::traits
        {
            typedef HashMapHdrTest::cmp   compare;
        };

        struct RCU_GPB_less_traits: public cc::michael_list::traits
        {
            typedef HashMapHdrTest::less  less;
        };

        struct RCU_GPB_cmpmix_traits: public cc::michael_list::traits
        {
            typedef HashMapHdrTest::cmp   compare;
            typedef HashMapHdrTest::less  less;
        };
    }

    void HashMapHdrTest::Michael_RCU_GPB_cmp()
    {
        typedef cc::MichaelKVList< rcu_type, int, HashMapHdrTest::value_type, RCU_GPB_cmp_traits > list;

        // traits-based version
        typedef cc::MichaelHashMap< rcu_type, list, map_traits > map;
        test_rcu< map >();

        // option-based version
        typedef cc::MichaelHashMap< rcu_type, list,
            cc::michael_map::make_traits<
                cc::opt::hash< hash_int >
                ,cc::opt::item_counter< simple_item_counter >
            >::type
        > opt_map;
        test_rcu< opt_map >();
    }

    void HashMapHdrTest::Michael_RCU_GPB_less()
    {
        typedef cc::MichaelKVList< rcu_type, int, HashMapHdrTest::value_type, RCU_GPB_less_traits > list;

        // traits-based version
        typedef cc::MichaelHashMap< rcu_type, list, map_traits > map;
        test_rcu< map >();

        // option-based version
        typedef cc::MichaelHashMap< rcu_type, list,
            cc::michael_map::make_traits<
                cc::opt::hash< hash_int >
                ,cc::opt::item_counter< simple_item_counter >
            >::type
        > opt_map;
        test_rcu< opt_map >();
    }

    void HashMapHdrTest::Michael_RCU_GPB_cmpmix()
    {
        typedef cc::MichaelKVList< rcu_type, int, HashMapHdrTest::value_type, RCU_GPB_cmpmix_traits > list;

        // traits-based version
        typedef cc::MichaelHashMap< rcu_type, list, map_traits > map;
        test_rcu< map >();

        // option-based version
        typedef cc::MichaelHashMap< rcu_type, list,
            cc::michael_map::make_traits<
                cc::opt::hash< hash_int >
                ,cc::opt::item_counter< simple_item_counter >
            >::type
        > opt_map;
        test_rcu< opt_map >();
    }


} // namespace map

