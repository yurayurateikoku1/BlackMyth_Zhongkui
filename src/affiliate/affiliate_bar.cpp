#include "affiliate_bar.h"

AffiliateBar *AffiliateBar::addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size, AnchorType anchor)
{
    auto affiliateBar = new AffiliateBar();
    affiliateBar->init();
    affiliateBar->setAnchor(anchor);
    affiliateBar->setSize(size);
    if (parent)
    {
        affiliateBar->setParrent(parent);
        parent->addChild(affiliateBar);
    }

    return affiliateBar;
}

void AffiliateBar::render()
{
    auto position = _parrent->getRenderPosition() + _offset;
    if (_percentage > 0.7f)
    {
        _game.renderHBar(position, _size, _percentage, _color_high);
    }
    else if (_percentage > 0.3f)
    {
        _game.renderHBar(position, _size, _percentage, _color_mid);
    }
    else
    {
        _game.renderHBar(position, _size, _percentage, _color_low);
    }
}
