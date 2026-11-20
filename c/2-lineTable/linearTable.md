#define MaxSize 50 
typedef struct sqList
{
    /* data */
    ELemType data[MaxSize];
    int length;
}SqList;


#define InitSize 10
typedef struct {
    ELemType *data;
    int MaxSize,length;
}SeqList



L.data = (ElemType*) malloc(sizeof(ElemType)*InitSize);
L.data = new ElemType[InitSize] 

##
顺序表
 优缺点
 优点：1.可以随机存取  通过首地址和元素序号 O（1）；
      2.存储密度高 没有其他比如说指针什么的存储  
 缺点：1.元素插入 需要移动大量的元素
      2.不够灵活，存储空间比较连续
##




//SqList L;
void InitList(SqList &L) {
    L.Length = 0;
}


void InitList(SeqList &L) {
    L.data = (ElemType*) malloc(sizeof(ElemType)*InitSize);
    L.length = 0;
    L.MaxSize = InitSize;
}

#插入操作
bool ListInsert(SqList &L,int i,ElemType e) {
    if(i<1 || L.length+1) {
        return false;
    }
    if(L.length >= MaxSize) {
        return false; //
    }
    for(int j=L.length; j>=i;j--) {
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

O(1)
O(n)

bool ListInsert(SeqList &L,int i,ElemType e) {
    if(i<1 || L.length+1) {
        return false;
    }
    if(L.length >= L.MaxSize) {
        //应该是一个扩容函数
        if(ExpandList(L) != true) {
            return false;
        }
    }

    for(int j=L.length; j>=i;j--) {
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;

}

bool ExpandList(SeqList &L){
    //create new  copy
    newData = (ElemType*) malloc(sizeof(ElemType)*2*InitSize);
    //这里还要判断内存申请是否成功

    L.MaxSize = 2*InitSize;

    for(int i=0；i< L.length;i++) {
        newData[i]=L.data[i];
    }
    free(L.data);
    L.data = newData;
    return false;
}