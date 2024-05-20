// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.DataTypes;

public readonly record struct Version(byte Major, byte Minor)
{
    public override readonly string ToString() =>
        $"{Major}.{Minor}";
}
