#include <Geode/Geode.hpp>

using namespace geode::prelude;


#include <Geode/modify/CustomSongWidget.hpp>
class $modify(MyCustomSongWidget, CustomSongWidget) {
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn || m_customSongID < 1 || m_isRobtopSong) return true;

		CCSprite* copyBtnSpr = CCSprite::createWithSpriteFrameName("diffIcon_03_btn_001.png");
                copyBtnSpr->setScale(0.7f);

		CCMenuItemSpriteExtra* copyBtn = CCMenuItemSpriteExtra::create(copyBtnSpr, this, menu_selector(MyCustomSongWidget::onCopySongID));
		copyBtn->setPosition({m_downloadBtn->getPositionX() - 31.f, m_downloadBtn->getPositionY() - 5.f});
		if (isMusicLibrary) {
			copyBtn->setPosition(ccp(m_playbackBtn->getPositionX() + 60.f, m_playbackBtn->getPositionY() + 22.5f));
		} else if (showSongSelect) copyBtn->setPosition({m_selectSongBtn->getPositionX() + 19.f, m_selectSongBtn->getPositionY() + 60.f});
		copyBtn->setID("button"_spr);

		m_buttonMenu->addChild(copyBtn);

		return true;
	}

	void onCopySongID(CCObject* sender) {
		(void)clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Successfully copied song ID {}!", m_customSongID), NotificationIcon::Success, 1.f)->show();
	}
};
