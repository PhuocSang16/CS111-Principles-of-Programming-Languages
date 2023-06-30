/*
Ý tưởng:
    Duyệt từ phải sang trái và phục hồi trạng thái của các bình nước trước khi chúng được uống trên danh sách các người khách:
        - Đối với các khách hàng tiết kiệm (E), tìm phần tử nhỏ nhất từ phải sang trái.
        - Đối với các khách hàng hoang phí (W), tìm phần tử lớn nhất từ phải sang trái ngoại trừ các phần tử bằng K.
    Sau khi đã tìm được chỉ mục của các phần tử nói trên, ta phục hồi trạng thái bằng cách cộng thêm 1 tại vị trí chỉ số index và lặp lại N lần.

    Đề bài có nhiều kết quả, vì vậy dù kết quả chương trình có khác biệt so với output trong đề, tuy nhiên vẫn thỏa mãn yêu cầu đề bài.
*/
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int N, M, K;

    cin >> N >> M >> K;

    vector<char> types(N);

    for (int i = 0; i < N; ++i) cin >> types[i];

    vector<int> a(M);

    for (int i = 0; i < M; ++i) cin >> a[i];

    vector<int> result;

    for (int i = N - 1; i >= 0; --i)
    {
        if (types[i] == 'E')
        {
            int min_value = a[0];
            int min_idx = 0;

            for (int j = 1; j < M; ++j)
            {
                if (a[j] < min_value)
                {
                    min_value = a[j];
                    min_idx = j;
                }
            }
            a[min_idx] += 1;
            result.push_back(min_idx + 1);
        }
        else
        {
            int max_value = 0;
            int max_idx = -1;

            for (int j = M - 1; j >= 0; --j)
            {
                if (a[j] > max_value && a[j] != K)
                {
                    max_value = a[j];
                    max_idx = j;
                }
            }
            a[max_idx] += 1;
            result.push_back(max_idx + 1);
        }
    }

    for (int i = 0; i < result.size(); ++i) cout << result[i] << " ";
    cout << endl;

    return 0;
}
