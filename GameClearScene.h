#pragma once

#include "SceneBase.h"
#include "Message.h"

class GameClearScene : public SceneBase {
private:
    Message* message; // メッセージ表示用のインスタンス
    int clear_image; // クリアのロゴ画像
    int king_image; // 王様の画像
    int background_image; // 背景の画像
    int hero_images[5]; // 勇者の画像を分割した配列
    int hero_standby[5]; // 待機画像
    int hero_frame; // 勇者のアニメーションフレーム
    int hero_frame_count; // フレーム更新用カウンタ
    int hero_x; // 勇者のX座標
    int hero_y; // 勇者のY座標
    int hero_direction; // 勇者の向き (1: 右向き, -1: 左向き)
    int bgm;

    bool is_moving; // 勇者が移動しているかどうか
  
public:
    GameClearScene();
    ~GameClearScene();
    void Initialize()override;
    void Finalize()override;
    SCENE_TYPE Update(float delta_time);
    void Draw() const;
    SCENE_TYPE GetNowScene() const;
};