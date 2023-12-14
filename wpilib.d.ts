export interface Meter {
  value(): number;
  delete(): void;
}

export interface Foot {
  value(): number;
  delete(): void;
}

export interface Degree {
  value(): number;
  delete(): void;
}

export interface Radian {
  value(): number;
  delete(): void;
}

export interface Translation2d {
  X(): Meter;
  Y(): Meter;
  Distance(_0: Translation2d): Meter;
  plus(_0: Translation2d): Translation2d;
  Angle(): Rotation2d;
  delete(): void;
}

export interface Rotation2d {
  Degrees(): Degree;
  delete(): void;
}

export interface Pose2d {
  X(): Meter;
  Y(): Meter;
  Rotation(): Rotation2d;
  plus(_0: Transform2d): Pose2d;
  delete(): void;
}

export interface Transform2d {
  X(): Meter;
  Y(): Meter;
  Rotation(): Rotation2d;
  delete(): void;
}

export interface MainModule {
  Meter: {new(_0: number): Meter};
  Foot: {new(_0: number): Foot};
  Degree: {new(_0: number): Degree};
  Radian: {new(_0: number): Radian};
  Translation2d: {new(_0: Meter, _1: Meter): Translation2d};
  Rotation2d: {new(_0: Radian): Rotation2d};
  Pose2d: {new(): Pose2d};
  Transform2d: {new(): Transform2d};
}
