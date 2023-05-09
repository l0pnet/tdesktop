/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "media/stories/media_stories_view.h"

#include "media/stories/media_stories_controller.h"
#include "media/stories/media_stories_delegate.h"
#include "media/stories/media_stories_header.h"
#include "media/stories/media_stories_slider.h"
#include "media/stories/media_stories_reply.h"

namespace Media::Stories {

View::View(not_null<Delegate*> delegate)
: _controller(std::make_unique<Controller>(delegate)) {
}

View::~View() = default;

void View::show(
		const std::vector<Data::StoriesList> &lists,
		int index,
		int subindex) {
	_controller->show(lists, index, subindex);
}

void View::ready() {
	_controller->ready();
}

QRect View::contentGeometry() const {
	return _controller->layout().content;
}

rpl::producer<QRect> View::contentGeometryValue() const {
	return _controller->layoutValue(
		) | rpl::map([=](const Layout &layout) {
			return layout.content;
		}) | rpl::distinct_until_changed();
}

void View::updatePlayback(const Player::TrackState &state) {
	_controller->updateVideoPlayback(state);
}

bool View::subjumpAvailable(int delta) const {
	return _controller->subjumpAvailable(delta);
}

bool View::subjumpFor(int delta) const {
	return _controller->subjumpFor(delta);
}

bool View::jumpFor(int delta) const {
	return _controller->jumpFor(delta);
}

bool View::paused() const {
	return _controller->paused();
}

void View::togglePaused(bool paused) {
	_controller->togglePaused(paused);
}

SiblingView View::siblingLeft() const {
	return _controller->siblingLeft();
}

SiblingView View::siblingRight() const {
	return _controller->siblingRight();
}

rpl::lifetime &View::lifetime() {
	return _controller->lifetime();
}

} // namespace Media::Stories