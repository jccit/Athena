/**
 * Creating a sidebar enables you to:
 - create an ordered group of docs
 - render a sidebar for each doc of that group
 - provide next/previous navigation

 The sidebars can be generated from the filesystem, or explicitly defined here.

 Create as many sidebars as you want.
 */

module.exports = {
  // By default, Docusaurus generates a sidebar from the docs folder structure
  guideSidebar: [
    'guides/welcome',
    'guides/architecture',
    {
      type: 'category',
      label: 'Components',
      items: [
        {type: 'autogenerated', dirName: 'guides/components'}
      ]
    },
    {
      type: 'category',
      label: 'Systems',
      items: [
        {type: 'autogenerated', dirName: 'guides/systems'}
      ]
    },
    {
      type: 'category',
      label: 'Scripting',
      items: [
        {type: 'autogenerated', dirName: 'guides/scripting'}
      ]
    }
  ],
  apiSidebar: [{type: 'autogenerated', dirName: 'api'}],

  // But you can create a sidebar manually
  /*
  tutorialSidebar: [
    {
      type: 'category',
      label: 'Tutorial',
      items: ['hello'],
    },
  ],
   */
};
