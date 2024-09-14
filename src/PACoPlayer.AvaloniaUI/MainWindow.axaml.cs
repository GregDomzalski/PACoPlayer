using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Platform.Storage;

namespace PACoPlayer.AvaloniaUI;

public partial class MainWindow : Window
{
    private static readonly IReadOnlyList<FilePickerFileType>? FileTypeFilter =
    [
        new("PACo Animation files") { Patterns = ["*"] },
    ];

    public MainWindow()
    {
        InitializeComponent();
    }

    protected override void OnDataContextChanged(EventArgs e)
    {
        base.OnDataContextChanged(e);

        if (DataContext is MainWindowViewModel viewModel) { viewModel.ShowOpenFileDialog = ShowOpenFileDialog; }
    }

    private async Task<string?> ShowOpenFileDialog()
    {
        IStorageProvider storageProvider = StorageProvider;

        IReadOnlyList<IStorageFile> file = await storageProvider.OpenFilePickerAsync(
            new()
            {
                AllowMultiple = false,
                FileTypeFilter = FileTypeFilter,
            });

        return file.Count > 0 ? file[0].Path.LocalPath : null;
    }
}
