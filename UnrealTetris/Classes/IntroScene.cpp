/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "IntroScene.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
    return IntroScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in IntroSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    auto colourLayer = LayerColor::create(Color4B(0x0, 0x4, 0x29, 0xFF), visibleSize.width, visibleSize.height);
    this->addChild(colourLayer);
    colourLayer->setPosition(origin.x, origin.y);
    colourLayer->setAnchorPoint(Vec2(0, 0));

    // add "IntroScene" splash screen"
    auto unral = Sprite::create("unral-teetris.png");

    unral->setAnchorPoint(Vec2(0.5f, 0.5f));
    unral->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    const auto visibleRatio = visibleSize.width / visibleSize.height;
    const auto unralRatio = unral->getContentSize().width / unral->getContentSize().height;

    if (unralRatio == visibleRatio) {
        // same proportion, set Xscale==Yscale and all will be well
        unral->setScale(unral->getContentSize().width / visibleSize.width, unral->getContentSize().height / visibleSize.height);

    } else if (unralRatio > visibleRatio) {
        // unral more widey, fit by width
        unral->setScaleX(visibleSize.width / unral->getContentSize().width );
        unral->setScaleY(unral->getScaleX());

    } else {
        // unral more heighty, fit by height
        unral->setScaleY(visibleSize.height / unral->getContentSize().height);
        unral->setScaleX(unral->getScaleY());
    }

    // add the sprite as a child to this layer
    this->addChild(unral);

    const auto totalTime = 0.9f;

    auto goAway = Spawn::create(
            RotateBy::create(totalTime, 360 * 3),
            FadeOut::create(totalTime),
            ResizeTo::create(totalTime, Size(0, 0)),
            nullptr
            );

    auto seq = Sequence::create(
            DelayTime::create(0.9f),
            goAway,
            CallFunc::create(
                    []() {
                        //Director::getInstance()->replaceScene(PlayingScene::createScene())
                        log("Changing to PlayingScene");
                    }
                    ),
            nullptr
            );

    unral->runAction(seq);

    log("helloworld");

    return true;
}


void IntroScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
