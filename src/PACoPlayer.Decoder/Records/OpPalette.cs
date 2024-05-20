// Copyright (c) GregDom LLC. All Rights Reserved.
// This file is licensed for use under the MIT license.

using System.Text;
using System.Text.Json.Serialization;
using PACoPlayer.Decoder.DataTypes;

namespace PACoPlayer.Decoder.Records;

public record OpPalette : OpHeader
{
    [JsonIgnore]
    private readonly byte _bits;

    public OpPalette(OpHeader header, byte bits) : base(header)
    {
        _bits = bits;
    }

    public PaletteType Type => (PaletteType)BitMask.Get(_bits, 5, 7);
    public PaletteTransitionWhen TransitionWhen => (PaletteTransitionWhen)BitMask.Get(_bits, 2, 7);
    public TransitionTime Time { get; init; } = TransitionTime.From(0);
    public Color SolidColor { get; init; } = new();
    public IReadOnlyList<Color> ColorTable { get; init; } = [];

    public override string ToString()
    {
        StringBuilder sb = new();

        _ = sb.AppendLine(base.ToString())
            .AppendLine($"- Transition type: {Type}, when: {TransitionWhen}, duration: {Time}")
            .AppendLine($"- Solid fill: {SolidColor}")
            .AppendLine($"- Color table: {ColorTable}");

        return sb.ToString();
    }
}
