// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

namespace PACoPlayer.Decoder.Records;

public record CycleGroup
{
    public int Start { get; init; }
    public int Count { get; init; }
    public int TicksPerChange { get; init; }
}
