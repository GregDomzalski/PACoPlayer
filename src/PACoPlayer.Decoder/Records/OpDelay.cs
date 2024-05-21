// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpDelay : OpHeader
{
    private readonly ushort _bits1;

    public OpDelay(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        _bits1 = reader.ReadUInt16BigEndian();
        reader.Skip(2); // Unused / filler bytes
    }

    /// <summary>
    /// Use this delay until the next delay opcode is seen.
    /// </summary>
    public bool Persist => BitMask.Get(_bits1, 15, 1) == 1;

    /// <summary>
    /// If true, the previous frame time is set to last timestamp.
    /// </summary>
    public bool ResetTimer => BitMask.Get(_bits1, 14, 1) == 1;

    /// <summary>
    /// If false, it's effectively a permanent ResetTimer = true.
    /// </summary>
    public bool MaintainFramerate => BitMask.Get(_bits1, 13, 1) == 1;

    /// <summary>
    /// If true, <see cref="Rate"/> is frames per second. Otherwise, it is ticks per second.
    /// </summary>
    public bool FramesPerSecond => BitMask.Get(_bits1, 12, 1) == 1;

    /// <summary>
    /// The number of frames or ticks per second, depending on the value of <see cref="FramesPerSecond"/>.
    /// </summary>
    public int Rate => (int)BitMask.Get(_bits1, 0, 0xFFF);

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Rate: {Rate} {(FramesPerSecond ? "frames per second" : "ticks per second")}");

        if (Persist) { _ = sb.AppendLine("- Persist"); }

        if (ResetTimer) { _ = sb.AppendLine("- Reset timer"); }

        if (MaintainFramerate) { _ = sb.AppendLine("- Maintain framerate"); }

        return sb.ToString();
    }
}
