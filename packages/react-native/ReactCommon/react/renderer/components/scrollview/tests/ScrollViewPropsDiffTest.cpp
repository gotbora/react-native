/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <react/renderer/components/scrollview/ScrollViewProps.h>
#include <react/test_utils/PropsPayloads.h>

#ifdef RN_SERIALIZABLE_STATE

namespace facebook::react {

namespace {

using folly::dynamic;

void expectPayloads(const std::vector<PropsCommit>& commits) {
  expectPayloadsMatchRawProps<ScrollViewProps>(commits);
}

} // namespace

// ReactScrollViewManager has a setter for it; with
// enableExclusivePropsUpdateAndroid there is no rawProps fallback.
TEST(ScrollViewPropsDiffTest, emitsScrollsChildToFocus) {
  expectPayloads({{dynamic::object("scrollsChildToFocus", false)}});
}

} // namespace facebook::react

#endif
