/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <react/renderer/components/view/ViewProps.h>
#include <react/test_utils/PropsPayloads.h>

#ifdef RN_SERIALIZABLE_STATE

namespace facebook::react {

namespace {

using folly::dynamic;

void expectPayloads(const std::vector<PropsCommit>& commits) {
  expectPayloadsMatchRawProps<ViewProps>(commits);
}

} // namespace

// ReactViewManager has setters for all three; with
// enableExclusivePropsUpdateAndroid there is no rawProps fallback.
TEST(ViewPropsDiffTest, emitsBackgroundSizePositionAndRepeat) {
  expectPayloads({{dynamic::object(
      "backgroundSize",
      dynamic::array(
          dynamic::object("x", "50%")("y", "auto"),
          dynamic::object("x", 20)("y", "25%")))(
      "backgroundPosition",
      dynamic::array(
          dynamic::object("top", "10%")("left", 5),
          dynamic::object("bottom", 0)("right", "20%")))(
      "backgroundRepeat",
      dynamic::array(dynamic::object("x", "no-repeat")("y", "space")))}});
}

// The Android transform parser knows `perspective`, not `perspectiveX`.
TEST(ViewPropsDiffTest, emitsPerspectiveUnderItsOwnName) {
  expectPayloads({{dynamic::object(
      "transform", dynamic::array(dynamic::object("perspective", 850)))}});
}

// ReactViewManager resets a side to `borderWidth` only for null (NaN); 0 keeps
// the side at width 0.
TEST(ViewPropsDiffTest, removingASideBorderWidthEmitsNull) {
  expectPayloads({
      {dynamic::object("borderWidth", 4)("borderLeftWidth", 12)},
      {dynamic::object("borderLeftWidth", nullptr)},
  });
}

// BoxShadow.parse defaults an absent color to black; 0 is transparent.
TEST(ViewPropsDiffTest, boxShadowWithoutColorOmitsColor) {
  expectPayloads({{dynamic::object(
      "boxShadow",
      dynamic::array(
          dynamic::object("offsetX", 0)("offsetY", 4)("blurRadius", 8)(
              "spreadDistance", 0)("inset", false)))}});
}

// FilterHelper defaults an absent drop shadow color to black; 0 is
// transparent.
TEST(ViewPropsDiffTest, dropShadowWithoutColorOmitsColor) {
  expectPayloads({{dynamic::object(
      "filter",
      dynamic::array(
          dynamic::object(
              "dropShadow",
              dynamic::object("offsetX", 0)("offsetY", 4)(
                  "standardDeviation", 4))))}});
}

} // namespace facebook::react

#endif
