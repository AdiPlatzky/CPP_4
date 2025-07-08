//12adi45@gmail.com

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace Container {

// תבנית גנרית שמאפשרת להחזיק כל סוג נתונים
template<typename T>
class MyContainer {
private:
    std::vector<T> data; // כאן נשמור את האיברים עצמם

public:
    MyContainer() = default;

    // הוספת איבר חדש
    void addElement(const T& element) {
        data.push_back(element);
    }

    // מחיקת איבר – מסיר את כל המופעים שלו, ואם לא קיים – זורק שגיאה
    void removeElement(const T& element) {
        auto it = std::remove(data.begin(), data.end(), element);
        if (it == data.end()) {
            throw std::runtime_error("Element not found!");
        }
        data.erase(it, data.end());
    }

    // החזרת גודל הקונטיינר
    size_t size() const {
        return data.size();
    }

    // אופרטור פלט – הדפסת כל הקונטיינר בסוגריים
    friend std::ostream& operator<<(std::ostream& os, const MyContainer& container) {
        os << "[";
        for (size_t i = 0; i < container.data.size(); ++i) {
            os << container.data[i];
            if (i != container.data.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    // ---------------------------
    // איטרטור: סדר רגיל (לפי סדר ההכנסה)
    // ---------------------------
    class OrderIterator {
    private:
        typename std::vector<T>::const_iterator it;
        typename std::vector<T>::const_iterator end;
    public:
        OrderIterator(typename std::vector<T>::const_iterator start,
                      typename std::vector<T>::const_iterator finish)
            : it(start), end(finish) {}

        const T& operator*() const { return *it; }
        OrderIterator& operator++() { ++it; return *this; }
        bool operator!=(const OrderIterator& other) const { return it != other.it; }
    };

    OrderIterator begin_order() const { return OrderIterator(data.begin(), data.end()); }
    OrderIterator end_order()   const { return OrderIterator(data.end(), data.end()); }

    // ---------------------------
    // איטרטור: סדר עולה (מהקטן לגדול)
    // ---------------------------
    class AscendingOrderIterator {
    private:
        std::vector<T> sortedData; // עותק ממוין
        size_t idx;
    public:
        AscendingOrderIterator(const std::vector<T>& originalData, size_t pos)
            : sortedData(originalData), idx(pos) {
            std::sort(sortedData.begin(), sortedData.end());
        }
        const T& operator*() const { return sortedData.at(idx); }
        AscendingOrderIterator& operator++() { ++idx; return *this; }
        bool operator!=(const AscendingOrderIterator& other) const { return idx != other.idx; }
    };

    AscendingOrderIterator begin_ascending_order() const {
        return AscendingOrderIterator(data, 0);
    }
    AscendingOrderIterator end_ascending_order() const {
        return AscendingOrderIterator(data, data.size());
    }

    // ---------------------------
    // איטרטור: סדר יורד (מהגדול לקטן)
    // ---------------------------
    class DescendingOrderIterator {
    private:
        std::vector<T> sortedData;
        size_t idx;
    public:
        DescendingOrderIterator(const std::vector<T>& originalData, size_t pos)
            : sortedData(originalData), idx(pos) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }
        const T& operator*() const { return sortedData.at(idx); }
        DescendingOrderIterator& operator++() { ++idx; return *this; }
        bool operator!=(const DescendingOrderIterator& other) const { return idx != other.idx; }
    };

    DescendingOrderIterator begin_descending_order() const {
        return DescendingOrderIterator(data, 0);
    }
    DescendingOrderIterator end_descending_order() const {
        return DescendingOrderIterator(data, data.size());
    }

    // ---------------------------
    // איטרטור: SideCrossOrder
    // עובר מהקצוות פנימה: קטן, גדול, שני בקטן, שני בגדול, וכו'
    // ---------------------------
    class SideCrossOrderIterator {
    private:
        std::vector<T> sideCrossData;
        size_t idx;
    public:
        SideCrossOrderIterator(const std::vector<T>& originalData, size_t pos)
            : idx(pos) {
            std::vector<T> sorted = originalData;
            std::sort(sorted.begin(), sorted.end());
            size_t left = 0;
            int right = static_cast<int>(sorted.size()) - 1;
            while (left <= right && !sorted.empty()) {
                if (left == right) {
                    sideCrossData.push_back(sorted[left]);
                    break;
                }
                sideCrossData.push_back(sorted[left++]);
                sideCrossData.push_back(sorted[right--]);
            }
        }
        const T& operator*() const { return sideCrossData.at(idx); }
        SideCrossOrderIterator& operator++() { ++idx; return *this; }
        bool operator!=(const SideCrossOrderIterator& other) const { return idx != other.idx; }
    };

    SideCrossOrderIterator begin_side_cross_order() const {
        return SideCrossOrderIterator(data, 0);
    }
    SideCrossOrderIterator end_side_cross_order() const {
        return SideCrossOrderIterator(data, data.size());
    }

    // ---------------------------
    // איטרטור: ReverseOrder – מהסוף להתחלה, לפי סדר ההכנסה!
    // ---------------------------
    class ReverseOrderIterator {
    private:
        const std::vector<T>& refData;
        int idx;
    public:
        ReverseOrderIterator(const std::vector<T>& data, int pos)
            : refData(data), idx(pos) {}
        const T& operator*() const { return refData.at(idx); }
        ReverseOrderIterator& operator++() { --idx; return *this; }
        bool operator!=(const ReverseOrderIterator& other) const { return idx != other.idx; }
    };

    ReverseOrderIterator begin_reverse_order() const {
        if (data.empty()) return ReverseOrderIterator(data, -1);
        return ReverseOrderIterator(data, static_cast<int>(data.size()) - 1);
    }
    ReverseOrderIterator end_reverse_order() const {
        return ReverseOrderIterator(data, -1);
    }

    // ---------------------------
    // איטרטור: MiddleOutOrder
    // מתחיל מהאמצע, אחר כך שמאלה-ימינה לסירוגין
    // ---------------------------
    class MiddleOutOrderIterator {
    private:
        std::vector<T> middleOutData;
        size_t idx;
    public:
        MiddleOutOrderIterator(const std::vector<T>& originalData, size_t pos)
            : idx(pos) {
            if (originalData.empty()) return;
            int n = static_cast<int>(originalData.size());
            int mid = n / 2;
            middleOutData.push_back(originalData[mid]);
            int left = mid - 1, right = mid + 1;
            bool goLeft = true;
            while (left >= 0 || right < n) {
                if (goLeft && left >= 0) {
                    middleOutData.push_back(originalData[left--]);
                } else if (right < n) {
                    middleOutData.push_back(originalData[right++]);
                }
                goLeft = !goLeft;
            }
        }
        const T& operator*() const { return middleOutData.at(idx); }
        MiddleOutOrderIterator& operator++() { ++idx; return *this; }
        bool operator!=(const MiddleOutOrderIterator& other) const { return idx != other.idx; }
    };

    MiddleOutOrderIterator begin_middle_out_order() const {
        return MiddleOutOrderIterator(data, 0);
    }
    MiddleOutOrderIterator end_middle_out_order() const {
        return MiddleOutOrderIterator(data, data.size());
    }

}; // סוף המחלקה

} //namespace Container
