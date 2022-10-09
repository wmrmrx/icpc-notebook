#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// iterator find_by_order(size_t index), size_t order_of_key(T key)
template <typename T> 
using ordered_set=__gnu_pbds::tree<T, __gnu_pbds::null_type,std::less<T>, __gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
