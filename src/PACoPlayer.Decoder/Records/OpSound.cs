// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;
using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record OpSound : OpHeader
{
    private readonly ushort _bits;

    public OpSound(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        _bits = reader.ReadUInt16BigEndian();
        DeferTillFrame = reader.ReadInt16BigEndian();
        Data = reader.ReadBytes(header.Length - 8).ToArray();
    }

    public bool Flush => BitMask.Get(_bits, 15, 1) == 1;
    public bool WaitStart => BitMask.Get(_bits, 14, 1) == 1;
    public bool WaitFinish => BitMask.Get(_bits, 13, 1) == 1;
    public SampleRate SampleRate => (SampleRate)BitMask.Get(_bits, 10, 7);
    public bool NoWaveData => BitMask.Get(_bits, 9, 1) == 1;

    public int DeferTillFrame { get; init; }
    public ReadOnlyMemory<byte> Data { get; init; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Sample rate: {SampleRate}")
            .AppendLine($"- Defer until frame: {DeferTillFrame}");

        if (Flush) { _ = sb.AppendLine("- Flush"); }

        if (WaitStart) { _ = sb.AppendLine("- Wait start"); }

        if (WaitFinish) { _ = sb.AppendLine(" - Wait finish"); }

        if (NoWaveData) { _ = sb.AppendLine(" - No wave data"); }

        return sb.ToString();
    }
}
