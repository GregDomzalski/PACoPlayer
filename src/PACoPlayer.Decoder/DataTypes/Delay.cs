// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using ValueOf;

namespace PACoPlayer.Decoder.DataTypes;

public class Delay : ValueOf<short, Delay>
{
    public override string ToString() =>
        $"{Value}";
}
