/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <react/renderer/components/image/ImageProps.h>
#include <react/test_utils/PropsPayloads.h>

#ifdef RN_SERIALIZABLE_STATE

namespace facebook::react {

namespace {

using folly::dynamic;

// Props 2.0 serializes every field of a source, JS only the ones it sets.
void expectPayloads(const std::vector<PropsCommit>& commits) {
  expectPayloadsMatchRawProps<ImageProps>(commits, {"source"});
}

} // namespace

// ReactImageView.setSource reads width and height at the top level of each
// source when there are several, and ReactImageManager reads the request
// headers from the top-level headers prop, which JS derives from the first
// source.
TEST(ImagePropsDiffTest, multipleSourcesCarrySizesAndHeaders) {
  dynamic headers = dynamic::object("Authorization", "token");
  expectPayloads({{dynamic::object(
      "source",
      dynamic::array(
          dynamic::object("uri", "https://a")("width", 10)("height", 20)(
              "headers", headers),
          dynamic::object("uri", "https://b")("width", 30)("height", 40)))(
      "headers", headers)}});
}

} // namespace facebook::react

#endif
