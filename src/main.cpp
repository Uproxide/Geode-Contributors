#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/binding/ProfilePage.hpp>
#include <Geode/Bindings.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Loader.hpp>
#include <algorithm>
#include <set>
#include <cctype>
#include <matjson.hpp>

using namespace geode::prelude;

// sorry for the mess, im not the c++ coder lmfao

std::set<int> geodeContributors;
bool gotTheShit = false;

class $modify(ProfilePage) {
public:
    bool loadedOnce = false;

    void loadPageFromUserInfo(GJUserScore* p0) {
		ProfilePage::loadPageFromUserInfo(p0);

		if (!gotTheShit)
		{
			auto res = web::fetch("https://projectbdash.com/userrates/cont.txt");
			if (!res) {
				log::info("Failed to fetch Contributors! Your internet is probably hot ass rn :ned:");
			}
			else {
				auto data = res.value();
			
				std::istringstream iss(data);
				int tempid;

				while (iss >> tempid) {
					geodeContributors.insert(tempid);
				}
				gotTheShit = true;
			}
		}

        
															

		for (const auto& contributor : geodeContributors) {
			if (contributor == p0) {
				CCNode* first_letter = reinterpret_cast<CCNode*>(m_usernameLabel->getChildren()->objectAtIndex(0));
				auto spr = CCSprite::create("geode.png"_spr);
				auto badgeMenu = static_cast<cocos2d::CCMenu*>(this->getChildByID("bagde-menu"));
				spr->setScale(1.1f); // much better
				spr->setPosition(first_letter->convertToWorldSpace(getPosition()));
				spr->setPosition({spr->getPositionX() - 15.f, spr->getPositionY() + 10.f});
				spr->setID("geode-badge");
				badgeMenu->addChild(spr);

				auto ytbadge = static_cast<cocos2d::CCSprite*>(this->getChildren()->objectAtIndex(1));

				if (Loader::get()->isModLoaded("xanii.youtubers") && ytbadge) {
					ytbadge->setScale(0.4f);
					ytbadge->setPosition(ccp(220.4, 274.6));
					ytbadge->setZOrder(1);
				}
				else
				{
					// no error handling? this works too so erm
				}
			}
		}
	}

	void setupPageInfo(gd::string name, char const* chars) {
		ProfilePage::setupPageInfo(name,chars);

		auto ytbadge = static_cast<cocos2d::CCSprite*>(this->getChildren()->objectAtIndex(1));
		auto geodebadge = static_cast<cocos2d::CCSprite*>(this->getChildByID("geode-badge"));
		

		if (Loader::get()->isModLoaded("xanii.youtubers") && ytbadge && geodebadge) {
			ytbadge->setScale(0.4f);
			ytbadge->setPosition(ccp(220.4, 274.6));
		}
		else
		{
			// no error handling?
		}
	}
};
