/*
A Bloom filter is a space-efficient probabilistic data structure, that is used to test whether an element is a member of a set. 
False positive matches are possible, but false negatives are not; i.e. a query returns either "possibly in set" or "definitely not in set". 
Elements can be added to the set, but not removed (though this can be addressed with a "counting" filter). The more elements that are added 
to the set, the larger the probability of false positives.

Bloom filters are surprisingly simple: divide a memory area into buckets (one bit per bucket for a standard bloom filter; more -- typically 
four -- for a counting bloom filter). To insert a key, generate several hashes per key, and mark the buckets for each hash. To check if a 
key is present, check each bucket; if any bucket is empty, the key was never inserted in the filter. If all buckets are non-empty, though, 
the key is only probably inserted -- other keys' hashes could have covered the same buckets. Determining exactly how big to make the filter 
and how many hashes to use to achieve a given false positive rate is a solved problem

Algorithm description:
An empty Bloom filter is a bit array of m bits, all set to 0. There must also be k different hash functions defined, each of which maps or 
hashes some set element to one of the m array positions with a uniform random distribution.

To add an element, feed it to each of the k hash functions to get k array positions. Set the bits at all these positions to 1.

To query for an element (test whether it is in the set), feed it to each of the k hash functions to get k array positions. If any of the 
bits at these positions are 0, the element is definitely not in the set – if it were, then all the bits would have been set to 1 when it was 
inserted. If all are 1, then either the element is in the set, or the bits have by chance been set to 1 during the insertion of other elements, 
resulting in a false positive. In a simple Bloom filter, there is no way to distinguish between the two cases, but more advanced techniques 
can address this problem.
*/