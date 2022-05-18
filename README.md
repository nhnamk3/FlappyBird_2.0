# Báo cáo FlappyBird

## Hướng dẫn cài đặt:

- [ ]  Mở terminal gõ: `git clone [https://github.com/nhnamk3/FlappyBird_2.0.git](https://github.com/nhnamk3/FlappyBird_2.0.git)`
- [ ]  

## Mô tả chung về trò chơi:

  Người chơi sẽ phải điều khiển con chim để bay qua các ống nước di chuyển từ trái sang phía bên phải màn hình. Mỗi lần qua một ống nước người chơi sẽ được 1 điểm, khi va chạm phải ống nước người chơi sẽ thua cuộc.

## Ý tưởng chính của trò chơi:

Trò chơi được lấy ý tưởng từ trò FlappyBird của Nguyễn Hà Đông phát hành vào năm 2013.

## Mô tả tổng quan các tính năng trong game

- MENU: Hiển thị các nút bấm tương ứng với các tính năng trong game.
    - Nhấn PLAY: Chuyển về màn hình chơi game.
    - Nhấn OPTION: (Dự kiến) Sẽ cho phép người chơi chuyển đổi màu của con chim.
    - Nhấn QUIT: Thoát trò chơi.
    - Nhấn nút có hình loa: Bật tắt âm thanh trong trò chơi.
    - Nhấn nút có hình chấm hỏi: Hướng dẫn chơi game, nhấn ESC để quay về MENU.
- PLAY: Tại màn hình chơi game.
    - Nhấn chuột để điều khiển con chim bay lên.
- DIE: Hiển thị điểm chơi và điểm cao nhất cùng các nút bấm cho người chơi chọn.
    - Nhấn OK: Chơi lại.
    - Nhấn MENU: Quay về MENU.

## Các kĩ thuật lập trình được sử dụng

- Sử dụng các lớp để định nghĩa đối tượng.
- Sử dụng mảng động kết hợp với enum để dễ truy cập và tên có tính gợi nhớ.
- Sử dụng thư viện SDL2 để làm việc với đồ họa.
- 

## Hướng phát triển và điều tâm đắc rút ra từ chương trình

- Hướng phát triển:
    - Sẽ hoàn thiện mục OPTION để có thể cho phép người chơi thay đổi linh hoạt hình ảnh con chim.
    - Sẽ có những item mà cho con chim ăn có một số kĩ năng đặc biệt trong khoảng một thời gian ngắn như: bất tử, x2 điểm, …
    - Sẽ bay nhanh hơn nếu như điểm ngày càng cao.
- Điều tâm đắc:
    - Sự kết hợp của mảng và enum khiến cho ta xử lý các đối tượng cùng kiểu dữ liệu đc đơn giản, không tốn nhiều công sức khi phải khai báo và hủy quá nhiều lần.
    - Biết sử dụng kết thừa của hướng đối tượng làm code mạch lạc, dễ hiểu hơn.
    - Đặt tên biến có quy tắc làm đọc code dễ hiểu, dễ kiểm soát code hơn.

Link GitHub: 

[https://github.com/nhnamk3/FlappyBird_2.0.git](https://github.com/nhnamk3/FlappyBird_2.0.git)

Link Youtube: [Flappy Bird game coded by nhnamk3 using SDL2 - YouTube](https://youtu.be/ZanvzjeVsCQ)
#Báo cáo FlappyBird

## Hướng dẫn cài đặt:

- [ ]  Mở terminal gõ: `git clone [https://github.com/nhnamk3/FlappyBird_2.0.git](https://github.com/nhnamk3/FlappyBird_2.0.git)`
- [ ]  

## Mô tả chung về trò chơi:

  Người chơi sẽ phải điều khiển con chim để bay qua các ống nước di chuyển từ trái sang phía bên phải màn hình. Mỗi lần qua một ống nước người chơi sẽ được 1 điểm, khi va chạm phải ống nước người chơi sẽ thua cuộc.

## Ý tưởng chính của trò chơi:

Trò chơi được lấy ý tưởng từ trò FlappyBird của Nguyễn Hà Đông phát hành vào năm 2013.

## Mô tả tổng quan các tính năng trong game

- MENU: Hiển thị các nút bấm tương ứng với các tính năng trong game.
    - Nhấn PLAY: Chuyển về màn hình chơi game.
    - Nhấn OPTION: (Dự kiến) Sẽ cho phép người chơi chuyển đổi màu của con chim.
    - Nhấn QUIT: Thoát trò chơi.
    - Nhấn nút có hình loa: Bật tắt âm thanh trong trò chơi.
    - Nhấn nút có hình chấm hỏi: Hướng dẫn chơi game, nhấn ESC để quay về MENU.
- PLAY: Tại màn hình chơi game.
    - Nhấn chuột để điều khiển con chim bay lên.
- DIE: Hiển thị điểm chơi và điểm cao nhất cùng các nút bấm cho người chơi chọn.
    - Nhấn OK: Chơi lại.
    - Nhấn MENU: Quay về MENU.

## Các kĩ thuật lập trình được sử dụng

- Sử dụng các lớp để định nghĩa đối tượng.
- Sử dụng mảng động kết hợp với enum để dễ truy cập và tên có tính gợi nhớ.
- Sử dụng thư viện SDL2 để làm việc với đồ họa.
- 

## Hướng phát triển và điều tâm đắc rút ra từ chương trình

- Hướng phát triển:
    - Sẽ hoàn thiện mục OPTION để có thể cho phép người chơi thay đổi linh hoạt hình ảnh con chim.
    - Sẽ có những item mà cho con chim ăn có một số kĩ năng đặc biệt trong khoảng một thời gian ngắn như: bất tử, x2 điểm, …
    - Sẽ bay nhanh hơn nếu như điểm ngày càng cao.
- Điều tâm đắc:
    - Sự kết hợp của mảng và enum khiến cho ta xử lý các đối tượng cùng kiểu dữ liệu đc đơn giản, không tốn nhiều công sức khi phải khai báo và hủy quá nhiều lần.
    - Biết sử dụng kết thừa của hướng đối tượng làm code mạch lạc, dễ hiểu hơn.
    - Đặt tên biến có quy tắc làm đọc code dễ hiểu, dễ kiểm soát code hơn.

Link GitHub: 

[https://github.com/nhnamk3/FlappyBird_2.0.git](https://github.com/nhnamk3/FlappyBird_2.0.git)

Link Youtube: [Flappy Bird game coded by nhnamk3 using SDL2 - YouTube](https://youtu.be/ZanvzjeVsCQ)
