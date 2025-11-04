# 🧮 Hash Table Benchmarking Framework

## 🧠 Giới thiệu

**Hash Table Benchmarking Framework** là một công cụ được xây dựng nhằm **đo lường và so sánh hiệu năng** giữa các kỹ thuật dò tìm (probing) trong **bảng băm (hash table)**. Chương trình hỗ trợ ba kỹ thuật phổ biến:

- 🔹 **Linear Probing**
- 🔸 **Quadratic Probing**
- ⚫ **Double Hashing**

Mục tiêu là giúp người đọc hiểu rõ **sự khác biệt về tốc độ, số lần probe, độ phân cụm (clustering)** và **mức độ hiệu quả** của từng phương pháp trong các tình huống tải khác nhau.

---

## ⚙️ Tính năng nổi bật

| Tính năng                          | Mô tả                                                                               |
| ---------------------------------- | ----------------------------------------------------------------------------------- |
| 🧩 **Ba phương pháp dò tìm**       | Linear, Quadratic, và Double Hashing                                                |
| ⚖️ **Hai hệ số tải (Load Factor)** | `LF1 = 0.5` và `LF2 = 0.9`                                                          |
| 🔄 **Hai chế độ hoạt động**        | Có hoặc không **rehash()** khi bảng đầy                                             |
| 📊 **Nhiều kiểu dữ liệu kiểm thử** | Random, Sequential, Clustered                                                       |
| ⏱️ **Thống kê chi tiết**           | Thời gian (insert/search/delete), số probe trung bình, cụm lớn nhất, cụm trung bình |
| 💾 **Xuất file CSV**               | Kết quả lưu trong `time.csv` và `clusters.csv`                                      |
| 🧱 **Dễ mở rộng**                  | Có thể thêm kỹ thuật băm hoặc loại dữ liệu khác                                     |

---

## 📁 Cấu trúc thư mục

```
hash_benchmark.cpp     // Mã nguồn chính
time.csv               // Kết quả thời gian (tự sinh)
clusters.csv           // Kết quả phân cụm (tự sinh)
README.md              // Tệp hướng dẫn (bạn đang đọc)
```

---

## 🚀 Cách chạy chương trình

### 1️⃣ Biên dịch

Sử dụng `g++` hoặc `clang++` (chuẩn C++17 trở lên):

```bash
g++ -O2 -std=c++17 -o benchmark hash_benchmark.cpp
```

### 2️⃣ Thực thi

```bash
./benchmark
```

Sau đó nhập danh sách kích thước kiểm thử:

```
Enter a list of the number of elements to test (space separated): 1000 5000 10000
```

Chương trình sẽ:

- Sinh ngẫu nhiên dữ liệu đầu vào
- Thực thi cả 3 kỹ thuật dò tìm
- Đo thời gian, số probe, cụm, ...
- Xuất kết quả ra file CSV

---

## 📊 Kết quả đầu ra

### 🧩 1. File `time.csv`

| Cột                        | Ý nghĩa                                        |
| -------------------------- | ---------------------------------------------- |
| Pattern                    | Kiểu dữ liệu (RANDOM / SEQUENTIAL / CLUSTERED) |
| Rehash                     | WITH / WITHOUT rehash                          |
| TestSize                   | Số phần tử                                     |
| InsLF1*\*, InsLF2*\*       | Thời gian chèn (μs) với LF1 và LF2             |
| SearchLF1*\*, SearchLF2*\* | Thời gian tìm kiếm (μs)                        |
| DelLF1*\*, DelLF2*\*       | Thời gian xóa (μs)                             |

🧭 **Ví dụ minh họa:**

```
Pattern,Rehash,TestSize,InsLF1_LH,InsLF1_QH,InsLF1_DH
RANDOM,WITH,5000,120.5,113.2,97.6
```

👉 Ở đây, Double Hashing (`DH`) cho thời gian thấp nhất → hiệu năng cao hơn.

---

### 🔗 2. File `clusters.csv`

| Cột      | Ý nghĩa               |
| -------- | --------------------- |
| Pattern  | Kiểu dữ liệu          |
| Rehash   | WITH / WITHOUT rehash |
| TestSize | Số phần tử            |
| Label    | LF1 hoặc LF2          |
| Max\_\*  | Độ dài cụm lớn nhất   |
| Avg\_\*  | Độ dài cụm trung bình |

📈 **Ví dụ minh họa:**

```
Pattern,Rehash,TestSize,Label,Max_LH,Avg_LH,Max_DH,Avg_DH
RANDOM,WITH,5000,LF1,12,3.2,6,1.8
```

➡️ Double Hashing tạo cụm nhỏ hơn → phân tán khóa tốt hơn.

---

## 🧩 Giải thích kỹ thuật

| Thuật toán            | Công thức probe                     | Đặc điểm                                               |
| --------------------- | ----------------------------------- | ------------------------------------------------------ |
| **Linear Probing**    | `h(k, i) = (h(k) + i) % m`          | Đơn giản, dễ cài đặt, nhưng dễ bị _primary clustering_ |
| **Quadratic Probing** | `h(k, i) = (h(k) + i²) % m`         | Giảm cụm liên tiếp, song vẫn có _secondary clustering_ |
| **Double Hashing**    | `h(k, i) = (h₁(k) + i × h₂(k)) % m` | Phân tán tốt, ít cụm, hiệu năng cao                    |

---

## 📈 Minh họa biểu đồ kết quả (Python)

Bạn có thể trực quan hóa dữ liệu bằng `matplotlib` và `pandas`:

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("time.csv")
random_data = df[df['Pattern'] == 'RANDOM']

plt.figure(figsize=(8,5))
plt.plot(random_data['TestSize'], random_data['InsLF1_LH'], 'o-', label='Linear')
plt.plot(random_data['TestSize'], random_data['InsLF1_QH'], 's-', label='Quadratic')
plt.plot(random_data['TestSize'], random_data['InsLF1_DH'], '^-', label='Double')

plt.title('Thời gian chèn (Insert) với Load Factor 0.5 - Dữ liệu Random')
plt.xlabel('Kích thước kiểm thử')
plt.ylabel('Thời gian (μs)')
plt.legend()
plt.grid(True)
plt.show()
```

🖼️ **Kết quả minh họa:**

```
Double Hashing ↓↓↓
|
|         ◇ Quadratic
|      ○ Linear
|____________________________________
        1000   5000   10000 → Số phần tử
```

Double Hashing có xu hướng ổn định và hiệu quả hơn khi kích thước tăng.

---

## ⚖️ Đánh giá & Ứng dụng

✅ **Ưu điểm:**

- Dễ dàng mở rộng, tùy chỉnh để kiểm tra thuật toán khác
- Cấu trúc rõ ràng, kết quả xuất ra CSV để phân tích nhanh
- Hữu ích cho sinh viên học **Cấu trúc dữ liệu & Giải thuật** hoặc nghiên cứu về hashing

⚠️ **Lưu ý:**

- Kết quả phụ thuộc vào kích thước bảng và hàm băm được chọn
- Với dữ liệu lớn, nên bật `-O2` hoặc `-O3` khi biên dịch để tối ưu tốc độ

---

## 📜 Giấy phép

Mã nguồn được chia sẻ miễn phí cho mục đích **học tập và nghiên cứu**.
