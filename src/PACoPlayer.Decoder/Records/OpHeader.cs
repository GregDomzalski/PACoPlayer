// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text.Json.Serialization;
using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record OpHeader
{
    [JsonIgnore]
    private readonly uint _bits;

    public OpHeader(uint bits)
    {
        _bits = bits;
    }

    public OpCodeKind Kind => (OpCodeKind)BitMask.Get(_bits, 24, 0xFF);
    public int Length => (int)BitMask.Get(_bits, 0, 0xFFFFFF);

    public override string ToString() =>
        $"OpCode: {Kind}";
}
