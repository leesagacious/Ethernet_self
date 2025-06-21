
static int nicmaj_probe(struct pci_dev *pdev,
		const struct pci_device_id *ent)
{
	int err, pci_using_dac;

	pci_using_dac = 0;

	err = dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64));
	if (!err) {
	
	} else {
	
	}
}	
