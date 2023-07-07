KEY CONCEPT: ASSIGNMENT OPERATORS

There are two points to keep in mind when you write an assignment operator:

• Assignment operators must work correctly if an object is assigned to itself.

• Most assignment operators share work with the destructor and copy constructor.

A good pattern to use when you write an assignment operator is to **ﬁrst copy the righthand operand into a local temporary. After the copy is done, it is safe to destroy the existing members of the left-hand operand. Once the left-hand operand is destroyed, copy the data from the temporary into the members of the left-hand operand.**



`=`赋值operator写法：要确保self- assignment 安全： 先建立一个等式右边的副本；再把原有左边的地址删了；再把**副本**的元素给左边的元素。

