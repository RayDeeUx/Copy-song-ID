#include <Geode/Geode.hpp>

using namespace geode::prelude;


#include <Geode/modify/CustomSongWidget.hpp>
class $modify(MyCustomSongWidget, CustomSongWidget) {

    struct Fields {
        bool m_hasInitialized;
        CCMenu* m_copySongIDMenu;
        CCMenuItemSpriteExtra* m_copySongIDButton;
    };
    
    bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
        if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;
        m_fields->m_hasInitialized = true;

        m_fields->m_copySongIDMenu = CCMenu::create();
        auto copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");

        if (isMusicLibrary) {
            this->addChildAtPosition(m_fields->m_copySongIDMenu, Anchor::BottomLeft, ccp(-142.f, -10.f));
            m_songIDLabel->setPosition(ccp(-131.f, -10.f));
            copySongIDButtonSprite->setScale(0.375f);
        } else {
            this->addChildAtPosition(m_fields->m_copySongIDMenu, Anchor::BottomLeft, ccp(-131.f, -27.f));
            m_songIDLabel->setPosition(ccp(-115.f, -27.f));
            copySongIDButtonSprite->setScale(0.5f);
        }

        m_fields->m_copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
        m_fields->m_copySongIDMenu->addChildAtPosition(m_fields->m_copySongIDButton, Anchor::Center);

        m_fields->m_copySongIDButton->setID("copy-song-id-button");
        m_fields->m_copySongIDMenu->setID("copy-song-id-menu");


        return true;
    }

    void positionInfoObjects() {
        CustomSongWidget::positionInfoObjects();
        if (!m_fields->m_hasInitialized) return;

        if (m_isMusicLibrary) {
            m_fields->m_copySongIDMenu->setPosition(ccp(-142.f, -10.f));
            m_songIDLabel->setPosition(ccp(-131.f, -10.f));
        } else {
            m_fields->m_copySongIDMenu->setPosition(ccp(-131.f, -27.f));
            m_songIDLabel->setPosition(ccp(-115.f, -27.f));
        }
    }

    void onCopySongID(CCObject* sender) {
        bool hasSucceeded = clipboard::write(fmt::format("{}", m_customSongID));
        if (hasSucceeded) {
            Notification::create("Successfully copied song ID!", NotificationIcon::Success, 1.f)->show();
        } else {
            Notification::create("Failed to copy song ID.", NotificationIcon::Error, 1.f)->show();
        }
    }
};
