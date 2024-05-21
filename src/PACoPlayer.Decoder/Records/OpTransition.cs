// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;
using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record OpTransition : OpHeader
{
    private readonly byte _bits;

    public OpTransition(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        Type = (TransitionType)reader.ReadByte();
        _bits = reader.ReadByte();
        Duration = TimeSpan.FromMilliseconds(reader.ReadByte() * 100); // Value is in 1/10ths of second
        ChunkSize = reader.ReadByte();
        PartSize = reader.ReadByte();

        if (Type == TransitionType.CustomTransition) { CustomData = reader.ReadBytes(header.Length - 9).ToArray(); }
    }

    public TransitionType Type { get; init; }
    public bool ChangingAreaOnly => BitMask.Get(_bits, 7, 1) == 1;
    public bool Persist => BitMask.Get(_bits, 6, 1) == 1;
    public TimeSpan Duration { get; init; }
    public int ChunkSize { get; init; }
    public int PartSize { get; init; }
    public ReadOnlyMemory<byte> CustomData { get; init; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Type: {Type}")
            .AppendLine($"- Duration: {Duration.Milliseconds}ms")
            .AppendLine($"ChunkSize: {ChunkSize}, PartSize: {PartSize}");

        if (ChangingAreaOnly) { _ = sb.AppendLine("- Changing area only"); }

        if (Persist) { _ = sb.AppendLine("- Persist"); }

        return sb.ToString();
    }
}
