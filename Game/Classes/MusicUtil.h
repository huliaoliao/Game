/*******************************************************************************
处理音乐的类
若用此类管理音乐，需要：
1. 在开始游戏时（比如splash界面）调用MusicUtil::DoInit()进行初始化
2. 在AppDelegate::applicationDidEnterBackground中调用MusicUtil::PauseBackgroundMusic暂停背景音乐
3. 在AppDelegate::applicationWillEnterForeground中调用MusicUtil::EnterForeground恢复背景音乐
4. 在AppDelegate::~AppDelegate中调用MusicUtil::End结束音乐
5. 在游戏要退出时会自动保存当前的设置。如果想要手动保存设置（比如玩家切换了音乐或音效的开启就想立即保存），
   调用MusicUtil::SaveSettings。
********************************************************************************/

#ifndef __UTIL_MUSICUTIL_H__
#define __UTIL_MUSICUTIL_H__

#include "cocos2d.h"

namespace util {

class MusicUtil {
public:
	// 从文件中读取音乐设置
	static void DoInit();

	// 背景音乐是否开了
	static bool is_background_music_on() { return is_bg_music_on_; }

	// 设置背景音乐开关
	static void set_is_background_music_on(bool is_on) { is_bg_music_on_ = is_on; }

	// 特效声音是否开了
	static bool is_effect_music_on() { return is_effect_music_on_; }

	// 设置特效声音开关
	static void set_is_effect_music_on(bool is_on) { is_effect_music_on_ = is_on; }

	// 播放背景音乐
	 // bg_music_name: 背景音乐名字
	// is_loop: 是否循环播放
	static void PlayBackgroundMusic(const char *music_name, bool is_loop);

	// 暂停
	static void PauseBackgroundMusic();

	 // 恢复
	static void ResumeBackgroundMusic();

	// 停止
	static void StopBackgroundMusic();

	 // 播放特效声音，music_name为特效声音名字
	static void PlayEffectMusic(const char *effect_name);

	// 游戏进入前台
	static void EnterForeground();

	 // 保存设置到文件
	static void SaveSettings();

	// 结束音乐播放（在游戏将要退出时调用）
	static void End();

	// 停止所有声音
	static void stopAll();

	// 设置并保存音效音量
	static void setVolume(float fVolume);

	// 获得保存的音效音量
	static float getVolume();

	// 设置并保存背景音乐音量
	static void setBgMusicVolume(float fVolume);

	 // 获得保存的背景音乐音量
	static float getBgMusicVolume();

private:
	static bool	is_bg_music_on_;			// 背景音乐是否开了
	static bool	is_effect_music_on_;		// 特效声音是否开了
	static bool	is_playing_bg;				// 是否正在播放背景音乐
	static int	m_nMusicID;					// 正在播放的背景音乐的id
	static float	m_fEffectVolume;			// 音效音量
	static float	m_fBackgroundMusicVolume;	// 背景音乐音量
	static std::string bg_music_name_;		// 上次播放的背景音乐的名称
};

}

#endif // UTIL_MUSICUTIL_H_
