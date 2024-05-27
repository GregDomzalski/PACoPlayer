// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpFill : OpHeader
{
    public OpFill(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        Color = new()
        {
            Red = reader.ReadByte(),
            Green = reader.ReadByte(),
            Blue = reader.ReadByte(),
        };

        Index = Color.Red;
    }

    public int Index { get; init; }
    public Color Color { get; init; }

    public override string ToString() =>
        base.ToString();
}
