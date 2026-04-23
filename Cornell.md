const float size = 5;
  const float distance = -15;
  Vector3 nxnynz = {-size, -size * 1.5f, -size + distance};
  Vector3 nxnypz = {-size, -size * 1.5f, size + distance};
  Vector3 nxpynz = {-size, +size * 1.5f, -size + distance};
  Vector3 nxpypz = {-size, +size * 1.5f, size + distance};
  Vector3 pxnynz = {+size, -size * 1.5f, -size + distance};
  Vector3 pxnypz = {+size, -size * 1.5f, size + distance};
  Vector3 pxpynz = {+size, +size * 1.5f, -size + distance};
  Vector3 pxpypz = {+size, +size * 1.5f, size + distance};

  // Bottom
  triangles.push_back({nxnynz, nxnypz, pxnypz, orange_shader});
  triangles.push_back({nxnynz, pxnypz, pxnynz, orange_shader});

  // Top
  // triangles.push_back({nxpynz, pxpypz, nxpypz, orange_shader});
  // triangles.push_back({nxpynz, pxpynz, pxpypz, orange_shader});

  // Left
  triangles.push_back({nxnynz, nxpynz, nxnypz, orange_shader});
  triangles.push_back({nxpypz, nxnypz, nxpynz, orange_shader});

  // Right
  triangles.push_back({pxnynz, pxnypz, pxpynz, orange_shader});
  triangles.push_back({pxpypz, pxpynz, pxnypz, orange_shader});

  // Back
  triangles.push_back({nxpynz, nxnynz, pxpynz, orange_shader});
  triangles.push_back({pxnynz, pxpynz, nxnynz, orange_shader});
