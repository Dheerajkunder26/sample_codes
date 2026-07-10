Ring Buffer Explanation.

- Tail and head is used for travesing the data
- intitally the head and tail is set to zero
- put function is called writes all data till 7 to storage
- get function reads the data
- new data only can be added once the data os read from the storage at that time the tail an dhead becomes zeros so new 8 datas can be written