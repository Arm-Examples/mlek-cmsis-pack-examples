if [[ -n "${{ env.ARM_UBL_ACTIVATION_CODE }}" ]]; then
    armlm activate --code ${{ env.ARM_UBL_ACTIVATION_CODE }}
else
    armlm activate --server https://mdk-preview.keil.arm.com --product KEMDK-COM0
fi