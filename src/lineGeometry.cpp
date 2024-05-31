#include "lineGeometry.h"
#include <algorithm>

LineGeometry::LineGeometry() : xAxis_(nullptr), yAxis_(nullptr) {
  connect(this, &LineGeometry::dataChanged, this, &LineGeometry::updateData);
}

void LineGeometry::updateData() {
  clear();

  const int N = xs_.length();

  // Sanity Checks
  if (N < 2 || ys_.length() < 2)
    return;
  if (!xAxis_)
    return;
  if (!yAxis_)
    return;

  int stride = 3 * sizeof(float);

  QByteArray vertexData(6 * N * stride, Qt::Initialization::Uninitialized);
  float *p = reinterpret_cast<float *>(vertexData.data());

  auto xs = xAxis_->convert(xs_);
  auto ys = yAxis_->convert(ys_);

  std::vector<float> angles(xs.size());
  // Calculate derivatives
  for (int i = 1; i < N - 1; ++i) {
    auto angle = atan2(ys[i + 1] - ys[i - 1], xs[i + 1] - xs[i - 1]);
    angles[i] = angle + M_PI / 2;
  }
  angles[0] = M_PI / 2 + atan2(ys[1] - ys[0], xs[0] - xs[0]);
  angles[N - 1] =
      M_PI / 2 + atan2(ys[N - 1] - ys[N - 2], xs[N - 1] - xs[N - 2]);

  for (int i = 0; i < N - 1; i++) {
    *p++ = xs[i] + cos(angles[i]) * thickness_;
    *p++ = ys[i] + sin(angles[i]) * thickness_;
    *p++ = 0.0f;
    *p++ = xs[i] - cos(angles[i]) * thickness_;
    *p++ = ys[i] - sin(angles[i]) * thickness_;
    *p++ = 0.0f;
    *p++ = xs[i + 1] - cos(angles[i + 1]) * thickness_;
    *p++ = ys[i + 1] - sin(angles[i + 1]) * thickness_;
    *p++ = 0.0f;

    *p++ = xs[i + 1] - cos(angles[i + 1]) * thickness_;
    *p++ = ys[i + 1] - sin(angles[i + 1]) * thickness_;
    *p++ = 0.0f;
    *p++ = xs[i + 1] + cos(angles[i + 1]) * thickness_;
    *p++ = ys[i + 1] + sin(angles[i + 1]) * thickness_;
    *p++ = 0.0f;
    *p++ = xs[i] + cos(angles[i]) * thickness_;
    *p++ = ys[i] + sin(angles[i]) * thickness_;
    *p++ = 0.0f;
  }

  setVertexData(vertexData);
  setStride(stride);
  setBounds(QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(+1.0f, +1.0f, 0.0f));

  // setPrimitiveType(QQuick3DGeometry::PrimitiveType::TriangleStrip);

  addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0,
               QQuick3DGeometry::Attribute::F32Type);

  update();
}
