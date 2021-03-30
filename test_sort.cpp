#include <iostream>
#include <vector>
#include <string>

void printArray(std::vector<int>& array, std::string str = "")
{
    if (!str.empty()) {
        std::cout << str << std::endl;
    }

    for (auto& ele : array)
    {
        std::cout << ele << " ";
    }

    std::cout << std::endl;
}

//// 插入排序
// 简单插入排序
void insertSort(std::vector<int>& array)
{
    //// 简单插入排序基本思想：
    // 将无序序列中的数据插入到有序的序列中.
    // 时间复杂度：O(n^2)
    // 稳定排序

    //// 简单插入排序实现关键点：
    // 1. 双层循环
    // 2. 从后往前扫描移动插入
    if (array.empty()) {
        std::cout << "input array is empty" << std::endl;
        return ;
    }

    for (int i = 1; i < array.size(); i++)
    {
        //// 有序数组：如果从后插入，可以一个一个的把相关元素进行后移。
        //// 如果从前插入，则插入位置之后的元素，整体向后一位，实现比较麻烦
        //// 方法1：
        int temp = array.at(i);
        int j = 0;
        for (j = i - 1; j >= 0; j--)
        {
            if (temp < array.at(j)) {
                array[j + 1] = array.at(j);
            } else {
                break;
            }
        }

        array[j + 1] = temp;

        // 方法2：比方法1效率低了少许，多了一些无用循环和赋值步骤操作
        // int temp = array.at(i);
        // for (int j = i - 1; j >= 0; j--)
        // {
        //     if (temp < array.at(j)) {
        //         array[j + 1] = array.at(j);
        //         array[j] = temp;
        //     }
        // }
    }
}

// 希尔排序
void shellSort(std::vector<int>& array)
{
    //// 希尔排序基本思想：
    // 把序列按下标的一定增量分组，对每组使用直接插入排序算法排序；然后逐渐将增量减小,并重复上述过程，当增量减至1时，整个序列恰好被分为一组，算法便终止。
    // 希尔增量序列：{n/2,(n/2)/2....1}
    // 时间复杂度：O(n*log n)
    // 不稳定排序

    //// 希尔排序实现关键点：
    // 3层for循环 + 1个if

    if (array.empty()) {
        std::cout << "input array is empty" << std::endl;
        return ;
    }

    for (int gap = array.size() / 2; gap > 0; gap /= 2)
    {
        // 这一层的循环没有想到。本质上从插入排序的增量为1改为gap
        for (int i = gap; i < array.size(); i++)
        {
            // 从后往前扫描，同直接插入排序的思路
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (array.at(j) > array.at(j + gap)) {
                    int temp = array.at(j);
                    array[j] = array[j + gap];
                    array[j + gap] = temp;
                }
            }
        }
    }
}


//// 交换排序
// 冒泡排序
void bubbleSort(std::vector<int>& array)
{
    //// 冒泡排序基本思想：
    // 两个数比较大小，较大的数下沉，较小的数冒起来。
    // 时间复杂度：O(n^2)
    // 稳定排序

    //// 冒泡排序实现关键点：
    // 从后向前两两比较,第一个最小数的位置就排好了
    if (array.empty()) {
        std::cout << "input array is empty" << std::endl;
        return ;
    }

    for (int i = 0; i < array.size(); i++)
    {
        for (int j = array.size() - 1; j > i; j--)
        {
            if (array.at(j - 1) > array.at(j)) {
                int temp = array.at(j - 1);
                array[j - 1] = array.at(j);
                array[j] = temp;
            }
        }
    }
}

// 快速排序
void quickSort(std::vector<int>& array, int begin, int end)
{
    //// 快速排序基本思想：
    // 基于 哨兵 的使用
    // 时间复杂度：O(n*log n)
    // 不稳定排序

    //// 快速排序实现关键点：
    // 1. 挑选中间值，从右到左移动哨兵，在从左到右移动哨兵
    // 2. 递归分治排序
    if (array.empty()) {
        std::cout << "input array is empty" << std::endl;
        return ;
    }

    if (begin >= end) {
        return ;
    }

    int middle = array.at(begin);
    int i = begin;
    int j = end;
    while (i < j)
    {
        while (i < j && array.at(j) > middle) 
        {
            j--;
        }
        // 注意：此处不是交换，因为首个元素已被取值所以此处被覆盖也没关系
        array[i] = array[j];

        while (i < j && array.at(i) <= middle)
        {
            i++;
        }

        array[j] = array[i];
    }

    array[i] = middle;
    quickSort(array, begin , i - 1);
    quickSort(array, i + 1, end);
}

void quickSort(std::vector<int>& array)
{
    quickSort(array, 0, array.size() - 1);
}


//// 选择排序
void selectionSort(std::vector<int>& array)
{
    //// 选择排序基本思想：
    // 
    // 时间复杂度：O(n^2)
    // 不稳定排序

    //// 选择排序实现关键点：
    // 方法1：相比方法2 减少了赋值的次数
    for (int i = 0; i < array.size(); i++)
    {
        int nMinIndex = i;
        for (int j = i + 1; j < array.size(); j++)
        {
            if (array.at(nMinIndex) > array.at(j)) {
                nMinIndex = j;
            }
        }

        if (nMinIndex > i) {
            int temp = array.at(i);
            array[i] = array[nMinIndex];
            array[nMinIndex] = temp;
        }
    }

    // 方法2：
    for (int i = 0; i < array.size(); i++)
    {
        for (int j = i + 1; j < array.size(); j++)
        {
            if (array.at(i) > array.at(j)) {
                int temp = array.at(i);
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

//// 堆排序
// 向下调整法
/**
 * @param array [in] 输入要排序的数组
 * @param root  [in] 输入要调整的根节点下标索引号
 * @param n     [in] 整个排序数组的最大索引。注：非数组长度
*/
void adjustDown(std::vector<int>& array, int root, int n)
{
    int parent = root;
    int child = 2 * parent + 1;
    while (child <= n)
    {
        if (child + 1 <= n && array.at(child) < array.at(child + 1)) {
            child = child + 1;
        }

        if (array.at(child) > array.at(parent)) {
            int temp = array.at(parent);
            array[parent] = array[child];
            array[child] = temp;
        } else {
            break;
        }

        parent = child;
        child = 2 * parent + 1;
    }
}

// 构建堆
void heapCreateDown(std::vector<int>& array)
{
    int n = array.size();
    int lastNonLeaf = (n - 2) / 2;
    for (; lastNonLeaf >= 0; lastNonLeaf--)
    {
        adjustDown(array, lastNonLeaf, n - 1);
    }
}

// 升序排序
// 大顶堆 --> 升序
// 小顶堆 --> 降序
void heapSortDown(std::vector<int>& array)
{
    //// 堆排序基本思想：
    // 
    // 时间复杂度：O(n*log n)
    // 不稳定排序

    //// 堆排序实现关键点：
    // 1. 创建堆；
    // 2. 依次交换堆顶和末端数据，同步减少堆的节点数量进行堆的再次构建
    heapCreateDown(array);
    // printArray(array);
    int n = array.size();
    for (int i = n - 1; i > 0; i--)
    {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;

        // printArray(array);
        adjustDown(array, 0, i - 1);
        // printArray(array);
    }
}


//// 归并排序
void merge(std::vector<int>& array, int left, int mid, int right)
{
    std::vector<int> tmp;
    int leftIndex = left;
    int rightIndex = mid + 1;
    while (leftIndex <= mid && rightIndex <= right)
        tmp.emplace_back(array.at(leftIndex) < array.at(rightIndex) ? array.at(leftIndex++) : array.at(rightIndex++));

    while (leftIndex <= mid)
        tmp.emplace_back(array.at(leftIndex++));

    while (rightIndex <= right)
        tmp.emplace_back(array.at(rightIndex++));

    for (int i = 0; i < tmp.size(); i++)
        array[i + left] = tmp[i];
}

void mergeSort(std::vector<int>& array, int left, int right)
{
    if (left >= right) {
        return ;
    }

    int mid = left + ((right - left) >> 1);
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}
void mergeSort(std::vector<int>& array)
{
    //// 归并排序基本思想：
    // 
    // 时间复杂度：O(n*log n)
    // 稳定排序

    //// 归并排序实现关键点：
    if (array.size() < 2) {
        return ;
    }

    mergeSort(array, 0, array.size() - 1);
}


//// 基数排序
void radixSort(std::vector<int>& array)
{
    // TODO.
}


int main()
{
    std::vector<int> array = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    printArray(array, "==insert sort==");
    insertSort(array);
    printArray(array);

    array = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    printArray(array, "==shell sort==");
    shellSort(array);
    printArray(array);

    array = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    printArray(array, "==buddle sort==");
    bubbleSort(array);
    printArray(array);

    array = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    printArray(array, "==quick sort==");
    quickSort(array);
    printArray(array);

    array = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    printArray(array, "==selection sort==");
    selectionSort(array);
    printArray(array);

    array = {99, 5, 36, 7, 22, 17, 92, 12, 2, 19, 25, 28, 1, 46};
    printArray(array, "==heap sort==");
    heapSortDown(array);
    printArray(array);

    array = {99, 5, 36, 7, 22, 17, 92, 12, 2, 19, 25, 28, 1, 46};
    printArray(array, "==merge sort==");
    mergeSort(array);
    printArray(array);

    system("pause");

    return 0;
}