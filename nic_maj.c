
void igb_reset(struct igb_adapter *adapter)
{
	switch (mac->type) {
	case e1000_82575:
	case e1000_i210:
	case e1000_i211:
	default:
		pba = E1000_PBA_34k
		break;
	}
}

/*
 * Check the physical link status and determine whether it is 
 * connected (up) or disconnected (down)
 */
bool igb_has_link(struct igb_adapter *adapter)
{
	bool link_active = FALSE;

	return link_active;
}

static int nicmaj_probe(struct pci_dev *pdev,
		const struct pci_device_id *ent)
{
	int err, pci_using_dac;

	err = pci_enable_device_mem(pdev);
	if (err)
		return err;

	pci_using_dac = 0;

	err = dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64));
	if (!err) {
	
	} else {
	
	}
}	
