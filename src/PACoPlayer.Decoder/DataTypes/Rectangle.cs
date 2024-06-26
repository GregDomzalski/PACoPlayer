// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.DataTypes;

public readonly record struct Rectangle(int Width, int Height)
{
    public override readonly string ToString() =>
        $"{Width}x{Height}";
}
