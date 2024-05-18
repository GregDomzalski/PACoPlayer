// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text.Json.Serialization;

namespace PACoPlayer.Decoder.Records;

public record ChunkHeader
{
    [JsonIgnore]
    private readonly uint _bits;

    public ChunkHeader(uint bits)
    {
        _bits = bits;
    }

    public bool SoundOnly => BitMask.Get(_bits, 31, 1) == 1;
    public bool Skippable => BitMask.Get(_bits, 30, 1) == 1;
    public bool Combinable => BitMask.Get(_bits, 29, 1) == 1;
    public int Filler => (int)BitMask.Get(_bits, 24, 0x1F);
    public int Length => (int)BitMask.Get(_bits, 0, 0x00FFFFFF);
}
