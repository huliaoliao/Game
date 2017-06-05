#include "Musicutil.h"
#include "audio/include/AudioEngine.h"
#include "audio/include/SimpleAudioEngine.h"
using namespace std;
USING_NS_CC;
using namespace CocosDenshion;

namespace util 
{
	// 保存/读取音乐设置的key
	const char *const kMusicKey = "kMusicKey";
	const char *const kEffectKey = "kEffectKey";
	// 保存/读取音量的key
	const char *const kEffectVolumeKey = "kEffectVolumeKey";
	const char *const kBackgroundMusicVolumeKey = "kBackgroundMusicVolumeKey";

	bool MusicUtil::is_bg_music_on_ = true;
	bool MusicUtil::is_effect_music_on_ = true;
	bool MusicUtil::is_playing_bg = false;
	int MusicUtil::m_nMusicID = 0;
	float MusicUtil::m_fEffectVolume = 1.0f;
	float MusicUtil::m_fBackgroundMusicVolume = 1.0f;
	string MusicUtil::bg_music_name_ = "";

	void MusicUtil::DoInit()
	{
		// 读取音乐音效设置
		is_bg_music_on_ = UserDefault::getInstance()->getBoolForKey(kMusicKey, false);
		is_effect_music_on_ = UserDefault::getInstance()->getBoolForKey(kEffectKey, true);
		// 读取音量
		m_fEffectVolume = UserDefault::getInstance()->getFloatForKey(kEffectVolumeKey, 1.0f);
		m_fBackgroundMusicVolume = UserDefault::getInstance()->getFloatForKey(kBackgroundMusicVolumeKey, 1.0f);
	}

	void MusicUtil::PlayBackgroundMusic(const char *music_name, bool is_loop)
	{
		if (is_playing_bg)
		{
			return;
		}
		bg_music_name_ = music_name;
		if (is_bg_music_on_)
		{
			is_playing_bg = true;
			SimpleAudioEngine::getInstance()->playBackgroundMusic(music_name, true);
		}
	}

	void MusicUtil::PauseBackgroundMusic()
	{
		if (is_bg_music_on_)
		{
			//experimental::AudioEngine::pause(m_nMusicID);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}

	void MusicUtil::ResumeBackgroundMusic()
	{
		if (is_playing_bg)
		{
			if (is_bg_music_on_)
			{
				//experimental::AudioEngine::resume(m_nMusicID);
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
		}
	}

	void MusicUtil::StopBackgroundMusic()
	{
		is_playing_bg = false;
		//experimental::AudioEngine::stop(m_nMusicID);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

	void MusicUtil::PlayEffectMusic(const char *effect_name)
	{
		//	if (is_effect_music_on_)
		//{
		//experimental::AudioEngine::play2d(effect_name, false, m_fEffectVolume);
		SimpleAudioEngine::getInstance()->playEffect(effect_name);
		//	}
	}

	void MusicUtil::EnterForeground()
	{
		if (is_bg_music_on_)
		{
			//experimental::AudioEngine::resume(m_nMusicID);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}

	void MusicUtil::SaveSettings()
	{
		UserDefault::getInstance()->setBoolForKey(kMusicKey, is_bg_music_on_);
		UserDefault::getInstance()->setBoolForKey(kEffectKey, is_effect_music_on_);
		UserDefault::getInstance()->flush();
	}

	void MusicUtil::End()
	{
		SaveSettings();  // 游戏结束前保存一次设置，以免忘了游戏中忘记保存了
		//experimental::AudioEngine::end();
		SimpleAudioEngine::getInstance()->end();
	}

	void MusicUtil::stopAll()
	{
		//experimental::AudioEngine::stopAll();
	}

	void MusicUtil::setVolume(float fVolume)
	{
		log("MusicUtil::setVolume %f", fVolume);
		m_fEffectVolume = fVolume;
		SimpleAudioEngine::getInstance()->setEffectsVolume(m_fEffectVolume);
		UserDefault::getInstance()->setFloatForKey(kEffectVolumeKey, m_fEffectVolume);
		UserDefault::getInstance()->flush();
	}

	float MusicUtil::getVolume()
	{
		return m_fEffectVolume;
	}

	void MusicUtil::setBgMusicVolume(float fVolume)
	{
		log("MusicUtil::setBgMusicVolume %f", fVolume);
		m_fBackgroundMusicVolume = fVolume;
		//experimental::AudioEngine::setVolume(m_nMusicID, m_fBackgroundMusicVolume);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_fBackgroundMusicVolume);
		UserDefault::getInstance()->setFloatForKey(kBackgroundMusicVolumeKey, m_fBackgroundMusicVolume);
		UserDefault::getInstance()->flush();
	}

	float MusicUtil::getBgMusicVolume()
	{
		return m_fBackgroundMusicVolume;
	}
}
