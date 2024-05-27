// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using BinForge;

namespace PACoPlayer.Decoder.Records;

public record OpCycle : OpHeader
{
    public OpCycle(OpHeader header, ref SpanReader reader)
        : base(header)
    {
        Duration = reader.ReadUInt16BigEndian();
        UserInterruptable = reader.ReadByte() > 0;
        EatEvent = reader.ReadByte() > 0;
        GroupCount = reader.ReadInt16BigEndian();
        reader.Skip(2);

        Groups = new List<CycleGroup>(GroupCount);
        for (int i = 0; i < GroupCount; i++)
        {
            Groups[i] = new()
            {
                Start = reader.ReadByte(),
                Count = reader.ReadByte(),
                TicksPerChange = reader.ReadByte(),
            };
        }
    }

    public int Duration { get; }
    public bool UserInterruptable { get; }
    public bool EatEvent { get; }
    public int GroupCount { get; }
    public IList<CycleGroup> Groups { get; }

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Duration: {Duration}");

        if (UserInterruptable) { _ = sb.AppendLine("- UserInterruptable"); }

        if (EatEvent) { _ = sb.AppendLine("- EatEvent"); }

        _ = sb.AppendLine($"- Group count: {GroupCount}");

        return sb.ToString();
    }
}
